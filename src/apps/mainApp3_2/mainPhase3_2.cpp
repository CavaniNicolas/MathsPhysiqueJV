
#include <iostream>

// Include glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Main UI
#include "mainApp3_2/UserInterface.hpp"

// Include API between PhysicsEngine and Render libs
#include <API/ScenesAPI.hpp>

// Include PhysicsEngine library
#include <PhysicsEngine/GameEngine.hpp>
#include <PhysicsEngine/Quaternion.hpp>
#include <PhysicsEngine/RigidBody.hpp>
#include <PhysicsEngine/Scene.hpp>
#include <PhysicsEngine/Vector3D.hpp>
#include <PhysicsEngine/RigidBodyGravity.hpp>

// Include Render lib which uses opengl
#include <Render/Camera.hpp>
#include <Render/Mesh.hpp>
#include <Render/Renderer.hpp>
#include <Render/Scene.hpp>
#include <Render/Shader.hpp>
#include <Render/Window.hpp>

// Mesh Data
#include <Render/Data/OBJReader.hpp>
#include <Render/Mesh/Plan.hpp>

// Debug Printers
#include <PhysicsEngine/DebugUtils/RigidBodyPrinter.hpp>
#include <Render/DebugUtils/RenderedMeshPrinter.hpp>

int main()
{
    render::Window window(960, 540, "Moteur Physique");
    if(!window.init())
    {
        return -1;
    }

    UserInterface ui(window);
    std::shared_ptr<render::Camera> camera = std::make_shared<render::Camera>(960, 540, glm::vec3(0.0f, 15.0f, 80.0f));

    std::shared_ptr<engine::Scene> sceneEngine = std::make_shared<engine::Scene>();
    engine::GameEngine gameEngine = engine::GameEngine(sceneEngine);

    // Create physicsObjects
    // sport car
    std::shared_ptr<engine::RigidBody> sportCarObject = std::make_shared<engine::RigidBody>(
      engine::Vector3D(-10, 10, 30), engine::Vector3D(5, 0, 0), engine::Quaternion(0, 0, 1, 0), engine::Vector3D());
    sportCarObject->setG(1);

    // police car
    std::shared_ptr<engine::RigidBody> policeCarObject = std::make_shared<engine::RigidBody>(
      engine::Vector3D(10, 10, 30), engine::Vector3D(-5, 0, 0), engine::Quaternion(), engine::Vector3D());
    policeCarObject->setG(1);

    engine::RigidBodyPrinter::setRigidBody(sportCarObject);

    {
        // Create Meshes and RenderedMeshes
        std::shared_ptr<render::RenderedMesh> plan = std::make_shared<render::RenderedMesh>(
          render::mesh::Plan::getMesh(), std::string(RESOURCE_PATH) + render::mesh::Plan::getTexturePath());

        render::IO::OBJReader objReader;

        // sport Car
        render::Mesh sportCarMesh(objReader.readOBJFromFile(std::string(RESOURCE_PATH) + "objects/LowPolyCar1.obj"));
        std::shared_ptr<render::RenderedMesh> sportCarRenderedMesh =
          std::make_shared<render::RenderedMesh>(sportCarMesh, std::string(RESOURCE_PATH) + "textures/CarTexture1.png");

        // police Car
        render::Mesh policeCarMesh(objReader.readOBJFromFile(std::string(RESOURCE_PATH) + "objects/LowPolyCar2.obj"));
        std::shared_ptr<render::RenderedMesh> policeCarRenderedMesh = std::make_shared<render::RenderedMesh>(
          policeCarMesh, std::string(RESOURCE_PATH) + "textures/CarTexture2.png");

        std::shared_ptr<engine::RigidBodyGravity> gravity = std::make_shared<engine::RigidBodyGravity>();

        render::RenderedMeshPrinter::setRenderedMesh(sportCarRenderedMesh);

        // create shader, renderer, and sceneRender
        render::Shader shader(std::string(RESOURCE_PATH) + "shaders/basic.shader");
        render::Renderer renderer;
        std::shared_ptr<render::Scene> sceneRender = std::make_shared<render::Scene>(camera);

        // add objects to the render scene (objects we only render
        sceneRender->addRenderedMesh(plan);
        // scale the renderedMesh
        plan->setScale(glm::vec3(50.0f, 50.0f, 50.0f));
        plan->setNeedModelUpdate(true);

        // Create the main API Scene
        api::ScenesAPI scenesAPI(sceneEngine, sceneRender);

        // add physicsObjects to the main scene
        scenesAPI.addPhysicsObject(sportCarObject, sportCarRenderedMesh);
        scenesAPI.addPhysicsObject(policeCarObject, policeCarRenderedMesh);

        bool crashHappening = false;
        bool crashStarted = false;
        int maxForceNb = 100;
        int forceNb = 0;

        while(!window.isBeingClosed())
        {
            if(!crashStarted &&
               (sportCarObject->getPosition().getX() >= -2 || policeCarObject->getPosition().getX() <= 2))
            {
                crashHappening = true;
                crashStarted = true;
                /*sportCarObject->setVelocity(engine::Vector3D());
                policeCarObject->setVelocity(engine::Vector3D());*/
                sportCarObject->addForceAtBodyPoint(engine::Vector3D(-10, 2, 0), engine::Vector3D(-1, -1, 0));
                policeCarObject->addForceAtBodyPoint(engine::Vector3D(10, 2, 0), engine::Vector3D(1, -1, 0));

                sceneEngine->addForceToAllRigidBodies(gravity);
            }

            if(crashHappening && forceNb < maxForceNb)
            {
                forceNb++;
                sportCarObject->addForce(engine::Vector3D(-5, 2, 0));
                policeCarObject->addForce(engine::Vector3D(5, 2, 0));
            }

            // Render Here
            // Clean the back buffer and depth buffer
            renderer.clear();

            // Start UI
            ui.start();

            // bind the shader
            shader.bind();

            // get the actual particles positions to set it to the corresponding renderedMeshes
            scenesAPI.updateMeshMatrix();

            // update model matrix if necessary and update camera
            sceneRender->update(window);

            engine::RigidBodyPrinter::debugPrint();
            render::RenderedMeshPrinter::debugPrint();

            // bind everything and call drawElements
            renderer.draw(shader, *sceneRender);

            // RenderUI
            ui.render(gameEngine, scenesAPI, *camera);

            // Swap buffers
            glfwSwapBuffers(window.getWindow());
            glfwPollEvents();

        } // Check if the ESC key was pressed or the window was closed
    }

    // Destroy UI
    ui.terminate();

    window.terminate();

    return 0;
}

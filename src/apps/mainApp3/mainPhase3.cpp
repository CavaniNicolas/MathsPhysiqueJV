
// Include glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

#include "mainApp3/UserInterface.hpp"

// Include API between PhysicsEngine and Render libs
#include <API/ScenesAPI.hpp>

// Include PhysicsEngine library
#include <PhysicsEngine/GameEngine.hpp>
#include <PhysicsEngine/Quaternion.hpp>
#include <PhysicsEngine/RigidBody.hpp>
#include <PhysicsEngine/Scene.hpp>
#include <PhysicsEngine/Vector3D.hpp>

#include <PhysicsEngine/DebugUtils/RigidBodyPrinter.hpp>

// Include Render lib which uses opengl
#include <Render/Camera.hpp>
#include <Render/Mesh.hpp>
#include <Render/Renderer.hpp>
#include <Render/Scene.hpp>
#include <Render/Shader.hpp>
#include <Render/Window.hpp>

#include <Render/Mesh/Plan.hpp>

#include "Render/Data/OBJReader.hpp"

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
    std::shared_ptr<engine::RigidBody> carObject = std::make_shared<engine::RigidBody>(
      engine::Vector3D(0, 30, 0), engine::Vector3D(1, 0, 0), engine::Quaternion(), engine::Vector3D());

    carObject->addForce(engine::Vector3D(1, 0, 0));

    engine::RigidBodyPrinter::setRigidBody(carObject);

    {
        // Create Meshes and RenderedMeshes
        std::shared_ptr<render::RenderedMesh> plan = std::make_shared<render::RenderedMesh>(
          render::mesh::Plan::getMesh(), std::string(RESOURCE_PATH) + render::mesh::Plan::getTexturePath());

        render::IO::OBJReader objReader;
        render::Mesh carMesh(objReader.readOBJFromFile(std::string(RESOURCE_PATH) + "objects/LowPolyCar1.obj"));

        std::shared_ptr<render::RenderedMesh> carRenderedMesh =
          std::make_shared<render::RenderedMesh>(carMesh, std::string(RESOURCE_PATH) + "textures/CarTexture1.png");

        render::RenderedMeshPrinter::setRenderedMesh(carRenderedMesh);

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
        scenesAPI.addPhysicsObject(carObject, carRenderedMesh);

        while(!window.isBeingClosed())
        {
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

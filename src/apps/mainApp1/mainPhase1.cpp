
// Include glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

#include "mainApp1/UserInterface.hpp"

// Include API between PhysicsEngine and Render libs
#include <API/ParticleMeshRegistry.hpp>

// Include PhysicsEngine library
#include <PhysicsEngine/DebugUtils/ParticlePrinter.hpp>

#include <PhysicsEngine/Bullet.hpp>
#include <PhysicsEngine/Fireball.hpp>
#include <PhysicsEngine/Laser.hpp>
#include <PhysicsEngine/GameEngine.hpp>
#include <PhysicsEngine/ParticleAnchoredSpring.hpp>
#include <PhysicsEngine/ParticleDrag.hpp>
#include <PhysicsEngine/ParticleForceRegistry.hpp>
#include <PhysicsEngine/ParticleGravity.hpp>
#include <PhysicsEngine/ParticleSpring.hpp>
#include <PhysicsEngine/Scene.hpp>
#include <PhysicsEngine/WallContactGenerator.hpp>

// Include Render lib which uses opengl
#include <Render/Camera.hpp>
#include <Render/Mesh.hpp>
#include <Render/RenderedMesh.hpp>
#include <Render/Renderer.hpp>
#include <Render/Scene.hpp>
#include <Render/Shader.hpp>
#include <Render/Window.hpp>

int main()
{
    render::Window window(960, 540, "Moteur Physique");
    if(!window.init())
    {
        return -1;
    }

    UserInterface ui(window);

    // Store mesh data in vectors for the mesh
    std::vector<render::Vertex> verts = {//              COORDINATES           /           TexCoord    //
                                         render::Vertex{glm::vec3(-5.0f, 0.0f, 5.0f), glm::vec2(0.32f, 0.32f)},
                                         render::Vertex{glm::vec3(5.0f, 0.0f, 5.0f), glm::vec2(0.69f, 0.32f)},
                                         render::Vertex{glm::vec3(5.0f, 0.0f, -5.0f), glm::vec2(0.69f, 0.69f)},
                                         render::Vertex{glm::vec3(-5.0f, 0.0f, -5.0f), glm::vec2(0.32f, 0.69f)},

                                         render::Vertex{glm::vec3(0.0f, 8.0f, 0.0f), glm::vec2(0.5f, 0.0f)},
                                         render::Vertex{glm::vec3(0.0f, 8.0f, 0.0f), glm::vec2(1.0f, 0.5f)},
                                         render::Vertex{glm::vec3(0.0f, 8.0f, 0.0f), glm::vec2(0.5f, 1.0f)},
                                         render::Vertex{glm::vec3(0.0f, 8.0f, 0.0f), glm::vec2(0.0f, 0.5f)}};

    std::vector<unsigned int> indices = {0, 1, 2, 2, 3, 0, 0, 1, 4, 1, 2, 5, 2, 3, 6, 3, 0, 7};

    render::Mesh pyramidMesh(verts, indices);

    // Store mesh data in vectors for the mesh
    std::vector<render::Vertex> vertsPlan = {//              COORDINATES           /           TexCoord //
                                             render::Vertex{glm::vec3(-5.0f, 0.0f, 5.0f), glm::vec2(0.0f, 0.0f)},
                                             render::Vertex{glm::vec3(-5.0f, 0.0f, -5.0f), glm::vec2(5.0f, 0.0f)},
                                             render::Vertex{glm::vec3(5.0f, 0.0f, -5.0f), glm::vec2(5.0f, 5.0f)},
                                             render::Vertex{glm::vec3(5.0f, 0.0f, 5.0f), glm::vec2(0.0f, 5.0f)}};

    std::vector<unsigned int> indicesPlan = {0, 1, 2, 2, 3, 0};

    render::Mesh planMesh(vertsPlan, indicesPlan);

    std::shared_ptr<render::Camera> camera = std::make_shared<render::Camera>(960, 540, glm::vec3(0.0f, 15.0f, 80.0f));

    // create a particle
    std::shared_ptr<Fireball> fireball = std::make_shared<Fireball>(Vector3D(0, 0, 0), Vector3D(1, 0, -1), 1, 1);

    std::shared_ptr<Scene> scene = std::make_shared<Scene>();
    scene->addParticle(fireball);

    std::shared_ptr<ParticleGravity> partGravity = std::make_shared<ParticleGravity>();
    std::shared_ptr<ParticleDrag> partDrag = std::make_shared<ParticleDrag>(0.25f, 0.0f);

    // link forces to fireball
    scene->addForce(fireball, partGravity);
    scene->addForce(fireball, partDrag);

    GameEngine gameEngine = GameEngine(scene);

    // Variable that help the rotation of the pyramid
    double prevTime = glfwGetTime();

    // Singleton to help debug and print Particle every 2 seconds
    ParticlePrinter::setParticle(fireball);

    {
        std::shared_ptr<render::RenderedMesh> pyramid = std::make_shared<render::RenderedMesh>(
          pyramidMesh, std::string(RESOURCE_PATH) + "textures/fire_texture_pyramid.png");

        std::shared_ptr<render::RenderedMesh> plan =
          std::make_shared<render::RenderedMesh>(planMesh, std::string(RESOURCE_PATH) + "textures/gril_texture.png");

        render::Shader shader(std::string(RESOURCE_PATH) + "shaders/basic.shader");

        render::Renderer renderer;

        render::Scene sceneRender(camera);
        sceneRender.addRenderedMesh(pyramid);
        sceneRender.addRenderedMesh(plan);

        ParticleMeshRegistry::addEntry(fireball, pyramid);

        // scale the renderedMeshes
        pyramid->setScale(glm::vec3(0.5f, 0.5f, 0.5f));
        plan->setScale(glm::vec3(50.0f, 50.0f, 50.0f));

        auto startTime = std::chrono::high_resolution_clock::now();

        while(!window.isBeingClosed())
        {
            // Render Here
            // Clean the back buffer and depth buffer
            renderer.clear();

            // Start UI
            ui.start();

            // bind the shader
            shader.bind();

            // Simple timer for the rotation
            double crntTime = glfwGetTime();
            if(crntTime - prevTime >= 1 / 144)
            {
                pyramid->addRotation(glm::vec3(0.0f, 0.5f, 0.0f));
                prevTime = crntTime;
            }

            ParticlePrinter::debugPrint();

            // get the actual particles positions to set it to the corresponding renderedMeshes
            ParticleMeshRegistry::updateMeshPosition();

            sceneRender.update(window);

            // bind everything and call drawElements
            // renderer.draw(shader, scene); // how it will be in the end (scene will
            // contain camera and list of meshes)
            renderer.draw(shader, *camera, *plan);

            // draw all particles
            ParticleMeshRegistry::drawAllParticles(renderer, shader, *camera);

            // RenderUI
            ui.render(gameEngine, *camera);

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

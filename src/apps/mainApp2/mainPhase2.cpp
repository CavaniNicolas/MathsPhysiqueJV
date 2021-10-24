
// Include glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

// Include API between PhysicsEngine and Render libs
#include <API/ParticleMeshRegistry.hpp>
#include <API/UserInterface.hpp>

// Include PhysicsEngine library
#include <PhysicsEngine/DebugUtils/ParticlePrinter.hpp>

#include <PhysicsEngine/Fireball.hpp>
#include <PhysicsEngine/GameEngine.hpp>
#include <PhysicsEngine/ParticleAnchoredSpring.hpp>
#include <PhysicsEngine/ParticleDrag.hpp>
#include <PhysicsEngine/ParticleForceRegistry.hpp>
#include <PhysicsEngine/ParticleGravity.hpp>
#include <PhysicsEngine/ParticleSpring.hpp>
#include <PhysicsEngine/WallContactGenerator.hpp>
#include <PhysicsEngine/ParticleRod.hpp>
#include <PhysicsEngine/ParticleCable.hpp>

// Include Render lib which uses opengl
#include <Render/Camera.hpp>
#include <Render/Mesh.hpp>
#include <Render/RenderedMesh.hpp>
#include <Render/Renderer.hpp>
#include <Render/Shader.hpp>
#include <Render/Window.hpp>

int main()
{
    Window window(960, 540, "Moteur Physique");
    if(!window.init())
    {
        return -1;
    }

    UserInterface ui(window);

    // Store mesh data in vectors for the mesh
    std::vector<Vertex> verts = {//              COORDINATES           /           TexCoord    //
                                 Vertex{glm::vec3(-5.0f, 0.0f, 5.0f), glm::vec2(0.32f, 0.32f)},
                                 Vertex{glm::vec3(5.0f, 0.0f, 5.0f), glm::vec2(0.69f, 0.32f)},
                                 Vertex{glm::vec3(5.0f, 0.0f, -5.0f), glm::vec2(0.69f, 0.69f)},
                                 Vertex{glm::vec3(-5.0f, 0.0f, -5.0f), glm::vec2(0.32f, 0.69f)},

                                 Vertex{glm::vec3(0.0f, 8.0f, 0.0f), glm::vec2(0.5f, 0.0f)},
                                 Vertex{glm::vec3(0.0f, 8.0f, 0.0f), glm::vec2(1.0f, 0.5f)},
                                 Vertex{glm::vec3(0.0f, 8.0f, 0.0f), glm::vec2(0.5f, 1.0f)},
                                 Vertex{glm::vec3(0.0f, 8.0f, 0.0f), glm::vec2(0.0f, 0.5f)}};

    std::vector<unsigned int> indices = {0, 1, 2, 2, 3, 0, 0, 1, 4, 1, 2, 5, 2, 3, 6, 3, 0, 7};

    Mesh pyramidMesh(verts, indices);

    // Store mesh data in vectors for the mesh
    std::vector<Vertex> vertsPlan = {//              COORDINATES           /           TexCoord //
                                     Vertex{glm::vec3(-5.0f, 0.0f, 5.0f), glm::vec2(0.0f, 0.0f)},
                                     Vertex{glm::vec3(-5.0f, 0.0f, -5.0f), glm::vec2(1.0f, 0.0f)},
                                     Vertex{glm::vec3(5.0f, 0.0f, -5.0f), glm::vec2(1.0f, 1.0f)},
                                     Vertex{glm::vec3(5.0f, 0.0f, 5.0f), glm::vec2(0.0f, 1.0f)}};

    std::vector<unsigned int> indicesPlan = {0, 1, 2, 2, 3, 0};

    Mesh planMesh(vertsPlan, indicesPlan);

    Camera camera(960, 540, glm::vec3(0.0f, 15.0f, 80.0f));

    std::vector<std::shared_ptr<Particle>> particles;

    // create a particle
    particles.push_back(std::make_shared<Particle>(Vector3D(0, 20, 0), Vector3D(10,10,0)));

    // create a particle
    particles.push_back(std::make_shared<Particle>(Vector3D(50, 20, 0), Vector3D()));

    Scene scene = Scene(particles);

    std::shared_ptr<ParticleGravity> partGravity = std::make_shared<ParticleGravity>();
    //std::shared_ptr<ParticleDrag> partDrag = std::make_shared<ParticleDrag>(.1, .05);

    // particle will fall due to gravity
    scene.addForce(partGravity);
    //scene.addForce(particle, partDrag);

    // create a floor the particle will bounce on
    std::shared_ptr<WallContactGenerator> floor =
      std::make_shared<WallContactGenerator>(particles[0], WallContactGenerator::y, 0, 0, 2);
    

    //create a rod between the particles
    std::shared_ptr<ParticleRod> rod = std::make_shared<ParticleRod>(particles[0], particles[1], 50);

    scene.addContactGenerator(floor);
    scene.addContactGenerator(rod);

    GameEngine gameEngine = GameEngine(scene);

    // Variable that help the rotation of the pyramid
    double prevTime = glfwGetTime();

    // Singleton to help debug and print Particle every 2 seconds
    ParticlePrinter::setParticle(particles[0]);

    {
        std::shared_ptr<RenderedMesh> pyramid =
          std::make_shared<RenderedMesh>(pyramidMesh, std::string(RESOURCE_PATH) + "textures/fire_texture_pyramid.png");
        std::shared_ptr<RenderedMesh> pyramid2 =
          std::make_shared<RenderedMesh>(pyramidMesh, std::string(RESOURCE_PATH) + "textures/fire_texture_pyramid.png");

        RenderedMesh plan(planMesh, std::string(RESOURCE_PATH) + "textures/gril_texture.png");

        Shader shader(std::string(RESOURCE_PATH) + "shaders/basic.shader");

        Renderer renderer;

        ParticleMeshRegistry::addEntry(particles[0], pyramid);
        ParticleMeshRegistry::addEntry(particles[1], pyramid2);

        // multiplay the plan scale by 5
        plan.setScale(glm::vec3(5.0f, 5.0f, 5.0f));

        // divide the pyramid scale by 2
        pyramid->setScale(glm::vec3(0.5f, 0.5f, 0.5f));
        pyramid2->setScale(glm::vec3(0.5f, 0.5f, 0.5f));

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

            plan.updateModelMatrix();

            ParticlePrinter::debugPrint();

            // get the actual particles positions to set it to the corresponding renderedMeshes
            ParticleMeshRegistry::updateMeshPosition();

            // handle inputs to move the camera
            camera.handleInputs(window);

            // fix the camera dimensions if the window gets resized
            {
                int width, height;
                glfwGetWindowSize(window.getWindow(), &width, &height);
                // Update the camera matrices view and proj
                camera.setSize(width, height);
                glViewport(0, 0, width, height);
            }

            // Update the camera matrices view and proj
            camera.update(0.1f, 10000.0f);

            // bind everything and call drawElements
            // renderer.draw(shader, scene); // how it will be in the end (scene will
            // contain camera and list of meshes)
            renderer.draw(shader, camera, plan);

            // draw all particles
            ParticleMeshRegistry::drawAllParticles(renderer, shader, camera);

            // RenderUI
            ui.render(gameEngine, camera);

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

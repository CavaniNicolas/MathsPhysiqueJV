
// Include GLEW (important to be first)
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

// Include glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <Windows.h>

#include "PhysicsEngine/Fireball.hpp"
#include "PhysicsEngine/GameEngine.hpp"

#include <Render/Camera.hpp>
#include <Render/Mesh.hpp>
#include <Render/RenderedMesh.hpp>
#include <Render/Renderer.hpp>
#include <Render/Shader.hpp>
#include <Render/UserInterface.hpp>
#include <Render/Window.hpp>

int main()
{
    Window window(960, 540, "Moteur Physique");
    if(!window.init())
    {
        return -1;
    }

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
                                     Vertex{glm::vec3(-5.0f, -1.0f, 5.0f), glm::vec2(0.0f, 0.0f)},
                                     Vertex{glm::vec3(-5.0f, -1.0f, -5.0f), glm::vec2(1.0f, 0.0f)},
                                     Vertex{glm::vec3(5.0f, -1.0f, -5.0f), glm::vec2(1.0f, 1.0f)},
                                     Vertex{glm::vec3(5.0f, -1.0f, 5.0f), glm::vec2(0.0f, 1.0f)}};

    std::vector<unsigned int> indicesPlan = {0, 1, 2, 2, 3, 0};

    Mesh planMesh(vertsPlan, indicesPlan);

    UserInterface ui(window);

    Camera camera(960, 540, glm::vec3(0.0f, 0.0f, 20.0f));

    // Enables the depth buffer (to properly render texture on 3d objects) (this
    // implies to clear GL_DEPTH_BUFFER_BIT in Renderer::clear();)
    GLCall(glEnable(GL_DEPTH_TEST));

    // Variable that help the rotation of the pyramid
    double prevTime = glfwGetTime();

    // create a projectile
    std::shared_ptr<Projectile> projectile;
    projectile = std::shared_ptr<Projectile>(new Fireball());
    projectile->setPosition(Vector3D());
    projectile->setDirection(Vector3D(1.0f, 0.0f, 0.0f));
    float duration = 5.0f;
    Scene scene = Scene({projectile});
    GameEngine gameEngine = GameEngine(scene);

    {
        RenderedMesh pyramid(pyramidMesh, std::string(RESOURCE_PATH) + "textures/fire_texture_pyramid.png");
        RenderedMesh plan(planMesh, std::string(RESOURCE_PATH) + "textures/gril_texture.png");

        Shader shader(std::string(RESOURCE_PATH) + "shaders/basic.shader");

        Renderer renderer;

        // divide by 2 the pyramid size
        pyramid.setScale(glm::vec3(0.5f, 0.5f, 0.5f));

        pyramid.setRotation(glm::vec3(0.0f, 0.5f, 0.0f));

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
                pyramid.updateModelMatrix();

                //                 // without updateModelMatrix, this used to work fine :(
                //                pyramid.rotate(0.5f, glm::vec3(0.0f, 1.0f, 0.0f));

                plan.rotate(-0.5f, glm::vec3(0.0f, 1.0f, 0.0f));
                prevTime = crntTime;
            }

            // get the actual particle position to set it to the pyramid
            pyramid.setPosition({gameEngine.getParticles()[0].getPosition().getX(),
                                 gameEngine.getParticles()[0].getPosition().getY(),
                                 gameEngine.getParticles()[0].getPosition().getZ()});

            // handle inputs to move the camera
            camera.handleInputs(window.getWindow());
            // Update the camera matrices view and proj
            camera.update(0.1f, 10000.0f);

            // bind everything and call drawElements
            // renderer.draw(shader, scene); // how it will be in the end (scene will
            // contain camera and list of meshes)
            renderer.draw(shader, camera, pyramid);
            renderer.draw(shader, camera, plan);

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


// Include glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

// Include Render lib which uses opengl
#include <Render/Camera.hpp>
#include <Render/Mesh.hpp>
#include <Render/Renderer.hpp>
#include <Render/Scene.hpp>
#include <Render/Shader.hpp>
#include <Render/Window.hpp>

#include "Render/Data/OBJReader.hpp"

int main()
{
    render::Window window(960, 540, "Moteur Physique");
    if(!window.init())
    {
        return -1;
    }

    std::shared_ptr<render::Camera> camera = std::make_shared<render::Camera>(960, 540, glm::vec3(0.0f, 15.0f, 80.0f));

    {
        render::IO::OBJReader objReader;
        objReader.readOBJFromFile(std::string(RESOURCE_PATH) + "objects/sphere1.obj");

        render::Shader shader(std::string(RESOURCE_PATH) + "shaders/basic.shader");

        render::Renderer renderer;

        std::shared_ptr<render::Scene> sceneRender = std::make_shared<render::Scene>(camera);

        while(!window.isBeingClosed())
        {
            // Render Here
            // Clean the back buffer and depth buffer
            renderer.clear();

            // bind the shader
            shader.bind();

            sceneRender->update(window);

            // bind everything and call drawElements
            renderer.draw(shader, *sceneRender);

            // Swap buffers
            glfwSwapBuffers(window.getWindow());
            glfwPollEvents();

        } // Check if the ESC key was pressed or the window was closed
    }

    window.terminate();

    return 0;
}

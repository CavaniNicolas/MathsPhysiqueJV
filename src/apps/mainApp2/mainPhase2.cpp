
// Include glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

#include "mainApp2/UserInterface.hpp"

// Include API between PhysicsEngine and Render libs
#include <API/ScenesAPI.hpp>

// Include PhysicsEngine library
#include <PhysicsEngine/GameEngine.hpp>
#include <PhysicsEngine/Scene.hpp>

#include <PhysicsEngine/DebugUtils/ParticlePrinter.hpp>

// Include Render lib which uses opengl
#include <Render/Camera.hpp>
#include <Render/Mesh.hpp>
#include <Render/Renderer.hpp>
#include <Render/Scene.hpp>
#include <Render/Shader.hpp>
#include <Render/Window.hpp>

#include <Render/Mesh/Plan.hpp>

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

    {
        std::shared_ptr<render::RenderedMesh> plan = std::make_shared<render::RenderedMesh>(
          render::mesh::Plan::getMesh(), std::string(RESOURCE_PATH) + render::mesh::Plan::getTexturePath());

        render::Shader shader(std::string(RESOURCE_PATH) + "shaders/basic.shader");

        render::Renderer renderer;

        std::shared_ptr<render::Scene> sceneRender = std::make_shared<render::Scene>(camera);
        sceneRender->addRenderedMesh(plan);

        api::ScenesAPI scenesAPI(sceneEngine, sceneRender);

        // scale the renderedMesh
        plan->setScale(glm::vec3(50.0f, 50.0f, 50.0f));
        plan->setNeedModelUpdate(true);

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

            sceneRender->update(window);

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

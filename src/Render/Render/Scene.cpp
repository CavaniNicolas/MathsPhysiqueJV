
#include "Render/Scene.hpp"

namespace render
{

Scene::Scene(std::shared_ptr<Camera> camera): m_camera(camera) {}

void Scene::update(Window& window)
{
    updateRenderedMeshes();
    updateCamera(window);
}

void Scene::updateCamera(Window& window)
{
    // handle inputs to move the camera
    m_camera->handleInputs(window);

    // fix the camera dimensions if the window gets resized
    {
        int width, height;
        glfwGetWindowSize(window.getWindow(), &width, &height);
        // Update the camera matrices view and proj
        m_camera->setSize(width, height);
        glViewport(0, 0, width, height);
    }

    // Update the camera matrices view and proj
    m_camera->update(0.1f, 10000.0f);
}

void Scene::updateRenderedMeshes()
{
    for(auto& renderedMesh: m_renderedMeshes)
    {
        if(renderedMesh->getNeedModelUpdate())
        {
            renderedMesh->updateModelMatrix();
        }
    }
}

void Scene::addRenderedMesh(std::shared_ptr<RenderedMesh> renderedMesh)
{
    m_renderedMeshes.push_back(renderedMesh);
}

} // namespace render

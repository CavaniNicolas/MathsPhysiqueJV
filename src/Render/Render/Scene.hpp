#pragma once

#include <memory>
#include <vector>

#include "Render/Camera.hpp"
#include "Render/RenderedMesh.hpp"
#include "Render/Window.hpp"

namespace render
{

class Scene
{
  public:
    Scene(std::shared_ptr<Camera> camera = std::make_shared<Camera>(960, 540, glm::vec3(0.0f, 15.0f, 80.0f)));

    void update(Window& window);
    void addRenderedMesh(std::shared_ptr<RenderedMesh> renderedMesh);

    std::shared_ptr<Camera> getCamera()
    {
        return m_camera;
    }

  private:
    std::vector<std::shared_ptr<RenderedMesh>> m_renderedMeshes;
    std::shared_ptr<Camera> m_camera;

    void updateCamera(Window& window);
    void updateRenderedMeshes();
};

} // namespace render

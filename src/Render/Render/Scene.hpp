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
    Scene(Camera& camera = Camera(960, 540, glm::vec3(0.0f, 15.0f, 80.0f)));

    void update(Window& window);
    void addRenderedMesh(std::shared_ptr<RenderedMesh> renderedMesh);

    Camera& getCamera()
    {
        return m_camera;
    }

  private:
    std::vector<std::shared_ptr<RenderedMesh>> m_renderedMeshes;
    Camera m_camera;

    void updateCamera(Window& window);
    void updateRenderedMeshes();
};

} // namespace render

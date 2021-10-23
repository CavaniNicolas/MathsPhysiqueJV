#pragma once

#include <vector>

#include "Render/Camera.hpp"
#include "Render/RenderedMesh.hpp"

namespace render
{

class Scene
{
  private:
    std::vector<RenderedMesh> m_renderedMeshes;
    Camera m_camera;

  public:
    Scene(Camera& camera = Camera(960, 540, glm::vec3(0.0f, 15.0f, 80.0f)));

    Camera& getCamera()
    {
        return m_camera;
    }
};

} // namespace render

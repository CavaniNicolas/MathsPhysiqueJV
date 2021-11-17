#pragma once

#include <vector>

#include <PhysicsEngine/PhysicsObject.hpp>
#include <Render/Camera.hpp>
#include <Render/RenderedMesh.hpp>
#include <Render/Renderer.hpp>
#include <Render/Shader.hpp>

namespace api
{

class PhysicsObjectMeshRegistry
{
  public:
    void addEntry(std::shared_ptr<engine::PhysicsObject> physicsObject,
                  std::shared_ptr<render::RenderedMesh> renderedMesh);

    void updateMeshMatrixFromPhysicsObject();
    int getSize() const
    {
        return m_registry.size();
    }

  private:
    struct PhysicsObjectMeshEntry
    {
        std::weak_ptr<engine::PhysicsObject> physicsObject;
        std::weak_ptr<render::RenderedMesh> renderedMesh;
    };

    std::vector<PhysicsObjectMeshEntry> m_registry;
};

} // namespace api

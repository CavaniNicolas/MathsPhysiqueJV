#pragma once

#include <vector>

#include <PhysicsEngine/Particle.hpp>
#include <Render/Camera.hpp>
#include <Render/RenderedMesh.hpp>
#include <Render/Renderer.hpp>
#include <Render/Shader.hpp>

namespace api
{

class ParticleMeshRegistry
{
  public:
    void addEntry(std::shared_ptr<engine::Particle> particle, std::shared_ptr<render::RenderedMesh> renderedMesh);

    void updateMeshPosition();
    int getSize() const
    {
        return m_registry.size();
    }

  private:
    struct ParticleMeshEntry
    {
        std::weak_ptr<engine::Particle> particle;
        std::weak_ptr<render::RenderedMesh> renderedMesh;
    };

    std::vector<ParticleMeshEntry> m_registry;
};

} // namespace api

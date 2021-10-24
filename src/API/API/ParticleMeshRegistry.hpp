#pragma once

#include <vector>

#include <PhysicsEngine/Particle.hpp>
#include <Render/Camera.hpp>
#include <Render/RenderedMesh.hpp>
#include <Render/Renderer.hpp>
#include <Render/Shader.hpp>

class ParticleMeshRegistry
{
  public:
    void addEntry(std::shared_ptr<Particle> particle, std::shared_ptr<render::RenderedMesh> renderedMesh);

    void updateMeshPosition();

  private:
    struct ParticleMeshEntry
    {
        std::weak_ptr<Particle> particle;
        std::weak_ptr<render::RenderedMesh> renderedMesh;
    };

    std::vector<ParticleMeshEntry> m_registry;
};

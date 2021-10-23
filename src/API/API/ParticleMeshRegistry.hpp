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
    ParticleMeshRegistry(const ParticleMeshRegistry&) = delete;
    ParticleMeshRegistry& operator=(const ParticleMeshRegistry&) = delete;

    static ParticleMeshRegistry& get();

    static void addEntry(std::shared_ptr<Particle> particle, std::shared_ptr<render::RenderedMesh> renderedMesh)
    {
        get().addEntryI(particle, renderedMesh);
    }

    static void updateMeshPosition()
    {
        get().updateMeshPositionI();
    }
    static void drawAllParticles(render::Renderer& renderer, render::Shader& shader, render::Camera& camera)
    {
        get().drawAllParticlesI(renderer, shader, camera);
    }

  private:
    struct ParticleMeshEntry
    {
        std::shared_ptr<Particle> particle;
        std::shared_ptr<render::RenderedMesh> renderedMesh;
    };

    std::vector<ParticleMeshEntry> m_registry;

    void addEntryI(std::shared_ptr<Particle> particle, std::shared_ptr<render::RenderedMesh> renderedMesh);
    void updateMeshPositionI();
    void drawAllParticlesI(render::Renderer& renderer, render::Shader& shader, render::Camera& camera) const;

    ParticleMeshRegistry() {}
};

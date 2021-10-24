#pragma once

#include <memory>

#include <PhysicsEngine/Particle.hpp>
#include <PhysicsEngine/Scene.hpp>
#include <Render/RenderedMesh.hpp>
#include <Render/Scene.hpp>

#include "API/ParticleMeshRegistry.hpp"

namespace api
{

class ScenesAPI
{
  public:
    ScenesAPI(std::shared_ptr<Scene> sceneEngine, std::shared_ptr<render::Scene> sceneRender);

    void updateMeshPosition();

    void addParticle(std::shared_ptr<Particle> particle, std::shared_ptr<render::RenderedMesh> renderedMesh);
    void addParticleDefault(std::shared_ptr<Particle> particle);

  private:
    std::shared_ptr<Scene> m_sceneEngine;
    std::shared_ptr<render::Scene> m_sceneRender;

    api::ParticleMeshRegistry m_partMeshReg;
};

} // namespace api

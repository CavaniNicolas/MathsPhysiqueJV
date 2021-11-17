#pragma once

#include <memory>

#include <PhysicsEngine/Particle.hpp>
#include <PhysicsEngine/PhysicsObject.hpp>
#include <PhysicsEngine/Scene.hpp>
#include <Render/RenderedMesh.hpp>
#include <Render/Scene.hpp>

#include "API/PhysicsObjectMeshRegistry.hpp"

namespace api
{

class ScenesAPI
{
  public:
    ScenesAPI(std::shared_ptr<engine::Scene> sceneEngine, std::shared_ptr<render::Scene> sceneRender);

    void updateMeshMatrix();

    void addPhysicsObject(std::shared_ptr<engine::PhysicsObject> physicsObject,
                          std::shared_ptr<render::RenderedMesh> renderedMesh);
    void addParticleDefault(std::shared_ptr<engine::Particle> particle);

    std::shared_ptr<engine::Scene> getSceneEngine();

  private:
    std::shared_ptr<engine::Scene> m_sceneEngine;

    std::shared_ptr<render::Scene> m_sceneRender;

    api::PhysicsObjectMeshRegistry m_physicsObjectMeshReg;
};

} // namespace api

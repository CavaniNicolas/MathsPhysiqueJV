
#include "API/ScenesAPI.hpp"

namespace api
{

ScenesAPI::ScenesAPI(std::shared_ptr<Scene> sceneEngine, std::shared_ptr<render::Scene> sceneRender):
  m_sceneEngine(sceneEngine), m_sceneRender(sceneRender)
{
}

void ScenesAPI::addParticle(std::shared_ptr<Particle> particle, std::shared_ptr<render::RenderedMesh> renderedMesh)
{
    m_partMeshReg.addEntry(particle, renderedMesh);
}

void ScenesAPI::updateMeshPosition()
{
    m_partMeshReg.updateMeshPosition();
}

} // namespace api


#include "API/ScenesAPI.hpp"

namespace api
{

ScenesAPI::ScenesAPI(std::shared_ptr<Scene> sceneEngine, std::shared_ptr<render::Scene> sceneRender):
  m_sceneEngine(sceneEngine), m_sceneRender(sceneRender)
{
}

// get the actual particles positions to set it to the corresponding renderedMeshes
void ScenesAPI::updateMeshPosition()
{
    m_partMeshReg.updateMeshPosition();
}

// add a particle to the engine Scene and add its linked renderedMesh in the render Scene
void ScenesAPI::addParticle(std::shared_ptr<Particle> particle, std::shared_ptr<render::RenderedMesh> renderedMesh)
{
    m_partMeshReg.addEntry(particle, renderedMesh);
}

} // namespace api

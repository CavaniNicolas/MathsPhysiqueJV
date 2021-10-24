
#include "API/ScenesAPI.hpp"

#include "Render/Mesh/Pyramid.hpp"

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

// add a particle to the engine Scene and link a default renderedMesh to it
void ScenesAPI::addParticleDefault(std::shared_ptr<Particle> particle)
{
    std::shared_ptr<render::RenderedMesh> pyramid = std::make_shared<render::RenderedMesh>(
      render::mesh::Pyramid::getMesh(), std::string(RESOURCE_PATH) + render::mesh::Pyramid::getTexturePath());

    m_sceneRender->addRenderedMesh(pyramid);

    addParticle(particle, pyramid);
}

} // namespace api

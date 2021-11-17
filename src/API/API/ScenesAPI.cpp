
#include "API/ScenesAPI.hpp"

#include "Render/Mesh/Pyramid.hpp"

namespace api
{

ScenesAPI::ScenesAPI(std::shared_ptr<engine::Scene> sceneEngine, std::shared_ptr<render::Scene> sceneRender):
  m_sceneEngine(sceneEngine), m_sceneRender(sceneRender)
{
}

// get the actual particles positions to set it to the corresponding renderedMeshes
void ScenesAPI::updateMeshMatrix()
{
    m_physicsObjectMeshReg.updateMeshMatrixFromPhysicsObject();
}

// add a particle to the engine Scene and add its linked renderedMesh in the render Scene
// particles must not be added to the scenes before, it is done here
void ScenesAPI::addPhysicsObject(std::shared_ptr<engine::PhysicsObject> physicsObject,
                                 std::shared_ptr<render::RenderedMesh> renderedMesh)
{
    m_sceneEngine->addPhysicsObject(physicsObject);
    m_sceneRender->addRenderedMesh(renderedMesh);

    if(std::shared_ptr<engine::Particle> particle = std::dynamic_pointer_cast<engine::Particle>(physicsObject))
    {
        renderedMesh->setNeedModelUpdate(true);
    }

    m_physicsObjectMeshReg.addEntry(physicsObject, renderedMesh);
}

// add a particle to the engine Scene and link a default renderedMesh to it
// particles must not be added to the scenes before
void ScenesAPI::addParticleDefault(std::shared_ptr<engine::Particle> particle)
{
    std::shared_ptr<render::RenderedMesh> pyramid = std::make_shared<render::RenderedMesh>(
      render::mesh::Pyramid::getMesh(), std::string(RESOURCE_PATH) + render::mesh::Pyramid::getTexturePath());

    addPhysicsObject(particle, pyramid);
}

std::shared_ptr<engine::Scene> ScenesAPI::getSceneEngine()
{
    return m_sceneEngine;
}

} // namespace api

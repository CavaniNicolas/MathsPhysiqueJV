
#include <glm/glm.hpp>

#include "API/PhysicsObjectMeshRegistry.hpp"
#include "PhysicsEngine/Particle.hpp"
#include "PhysicsEngine/RigidBody.hpp"

namespace api
{

void PhysicsObjectMeshRegistry::addEntry(std::shared_ptr<engine::PhysicsObject> physicsObject,
                                         std::shared_ptr<render::RenderedMesh> renderedMesh)
{
    m_registry.push_back({physicsObject, renderedMesh});
}

void PhysicsObjectMeshRegistry::updateMeshMatrixFromPhysicsObject()
{
    for(auto const& entry: m_registry)
    {
        // creates a shared_ptr that manages the referenced object by the weak_ptr
        std::shared_ptr<render::RenderedMesh> renderedMesh = entry.renderedMesh.lock();
        std::shared_ptr<engine::PhysicsObject> physicsObject = entry.physicsObject.lock();

        if(std::shared_ptr<engine::Particle> particle = std::dynamic_pointer_cast<engine::Particle>(physicsObject))
        {
            // get the actual particle position to set it to the renderedMesh
            renderedMesh->setPosition(
              {particle->getPosition().getX(), particle->getPosition().getY(), particle->getPosition().getZ()});
        }
        else if(std::shared_ptr<engine::RigidBody> rigidBody =
                  std::dynamic_pointer_cast<engine::RigidBody>(physicsObject))
        {
            //            // get the Matrix34 from the engine but make it a glm::mat4
            //            glm::mat4 matrix = {}
            //            renderedMesh->setModelMatrix(matrix);
        }
    }
}

} // namespace api

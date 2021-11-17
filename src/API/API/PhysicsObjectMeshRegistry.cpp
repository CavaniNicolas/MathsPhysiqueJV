
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
            // get the Matrix34 from the engine but make it a glm::mat4
            std::array<std::array<float, 4>, 3> values = rigidBody->getTransformationMatrix().getValuesArray();

            glm::mat4 matrix({{values[0][0], values[0][1], values[0][2], values[0][3]},
                              {values[1][0], values[1][1], values[1][2], values[1][3]},
                              {values[2][0], values[2][1], values[2][2], values[2][3]},
                              {0, 0, 0, 1}});
            //            std::cout << matrix[0][0] << matrix[0][1] << matrix[0][2] << matrix[0][3] << std::endl;

            renderedMesh->setModelMatrix(matrix);
        }
    }
}

} // namespace api

#pragma once

#include "PhysicsEngine/RigidBody.hpp"
#include "PhysicsEngine/ForceGenerator.hpp"

namespace engine
{
class RigidBodyForceGenerator : public ForceGenerator
{
  protected:
    std::shared_ptr<RigidBody> checkRigidBody(std::shared_ptr<PhysicsObject> object)
    {
        if(std::shared_ptr<RigidBody> rigidBody = std::dynamic_pointer_cast<RigidBody>(object))
        {
            return rigidBody;
        }
        else
        {
            std::cerr << "Tried to apply a RigidBodyForce to a non rigidBody object." << std::endl;
            exit(EXIT_FAILURE);
        }
    }

  public:
    // We will check if the object is a particle before really applying the force
    virtual void updateForce(std::shared_ptr<PhysicsObject> object, float duration) = 0;
};
} // namespace engine
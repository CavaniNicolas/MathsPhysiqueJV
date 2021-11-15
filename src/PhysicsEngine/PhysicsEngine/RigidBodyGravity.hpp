#pragma once

#include "RigidBodyForceGenerator.hpp"

namespace engine
{
class RigidBodyGravity : public RigidBodyForceGenerator
{
  public:
    // Apply the gravity force to center of mass of the rigidbody
    void updateForce(std::shared_ptr<PhysicsObject> object, float duration) override;
};
} // namespace engine
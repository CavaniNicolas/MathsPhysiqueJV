#pragma once

#include "PhysicsEngine/RigidBodyForceGenerator.hpp"

namespace engine
{
class RigidBodySpring : public RigidBodyForceGenerator
{
  private:
    // Anchor point in the object's local coordinates
    Vector3D m_bodyAnchor;

    std::shared_ptr<RigidBody> m_otherRigidBody = nullptr;
    // Other anchor point in other object's local coordinates
    Vector3D m_otherBodyAnchor;

    // Spring parameters
    float m_k;
    float m_restLength;

  public:
    RigidBodySpring(
      Vector3D localAnchor, std::shared_ptr<RigidBody> otherRigidBody, Vector3D otherAnchor, float k, float restLength);

    // Transform each anchor point in world coordinates
    // Calculate the spring force and apply it at anchor point
    void updateForce(std::shared_ptr<PhysicsObject> object, float duration) override;
};
} // namespace engine
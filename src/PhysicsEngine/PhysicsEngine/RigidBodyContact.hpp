#pragma once

#include "PhysicsEngine/RigidBody.hpp"

namespace engine
{
class RigidBodyContact
{
  private:
    Vector3D m_contactPoint = Vector3D();
    Vector3D m_contactNormal = Vector3D();
    float m_penetration;

  public:
    RigidBodyContact(Vector3D contactPoint,
                     Vector3D contactNormal,
                     float penetration);

    RigidBodyContact() = default;

    Vector3D getContactPoint() const;
    Vector3D getContactNormal() const;
    float getPenetration() const;

    void setContactPoint(Vector3D contactPoint);
    void setContactNormal(Vector3D contactNormal);
    void setPenetration(float penetration);
};
} // namespace engine
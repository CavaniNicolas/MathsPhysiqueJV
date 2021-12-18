#include "PhysicsEngine/RigidBodyContact.hpp"

namespace engine
{
RigidBodyContact::RigidBodyContact(Vector3D contactPoint, Vector3D contactNormal, float penetration):
  m_contactPoint(contactPoint), m_contactNormal(contactNormal), m_penetration(penetration)
{
}

Vector3D RigidBodyContact::getContactPoint() const
{
    return m_contactPoint;
}
Vector3D RigidBodyContact::getContactNormal() const
{
    return m_contactNormal;
}
float RigidBodyContact::getPenetration() const
{
    return m_penetration;
}

void RigidBodyContact::setContactPoint(Vector3D contactPoint)
{
    m_contactPoint = contactPoint;
}
void RigidBodyContact::setContactNormal(Vector3D contactNormal)
{
    m_contactNormal = contactNormal;
}
void RigidBodyContact::setPenetration(float penetration)
{
    m_penetration = penetration;
}

} // namespace engine
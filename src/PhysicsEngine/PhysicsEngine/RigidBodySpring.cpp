#include "PhysicsEngine/RigidBodySpring.hpp"

using namespace engine;

RigidBodySpring::RigidBodySpring(
  Vector3D localAnchor, std::shared_ptr<RigidBody> otherRigidBody, Vector3D otherAnchor, float k, float restLength):
  m_bodyAnchor(localAnchor),
  m_otherRigidBody(otherRigidBody),
  m_otherBodyAnchor(otherAnchor),
  m_k(k),
  m_restLength(restLength)
{
}

// Transform each anchor point in world coordinates
// Calculate the spring force and apply it at anchor point
void RigidBodySpring::updateForce(std::shared_ptr<PhysicsObject> object, float duration)
{
    auto rigidbody = checkRigidBody(object);

    Vector3D bodyWorldCoordinates = rigidbody->localToWorldCoordinates(m_bodyAnchor);
    Vector3D otherWorldCoordinates = m_otherRigidBody->localToWorldCoordinates(m_otherBodyAnchor);

    Vector3D springLength = bodyWorldCoordinates - otherWorldCoordinates;

    Vector3D force = springLength.normalize() * -m_k * (springLength.getNorm() - m_restLength);

    rigidbody->addForceAtBodyPoint(force, m_bodyAnchor);
    m_otherRigidBody->addForceAtBodyPoint(force * (-1), m_otherBodyAnchor);
}
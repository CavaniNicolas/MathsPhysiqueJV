
#include "PhysicsEngine/BoundingSphere.hpp"
#include "PhysicsEngine/Vector3D.hpp"

namespace engine
{

bool BoundingSphere::collideWith(const BoundingSphere& other) const
{
    // get both rigidbodies' position
    std::shared_ptr<RigidBody> rb = m_rigidBody.lock();
    Vector3D rbPos = rb->getPosition();
    std::shared_ptr<RigidBody> otherRb = other.m_rigidBody.lock();
    Vector3D otherPos = otherRb->getPosition();

    // calculate distance between the two positions
    float difX = rbPos.getX() - otherPos.getX();
    float difY = rbPos.getY() - otherPos.getY();
    float difZ = rbPos.getZ() - otherPos.getZ();
    float distance = sqrt(difX * difX + difY * difY + difZ * difZ);

    // if the rigidBodies' bounding sphere collide, return true
    if(distance < m_radius + other.m_radius)
    {
        return true;
    }
    return false;
}

} // namespace engine

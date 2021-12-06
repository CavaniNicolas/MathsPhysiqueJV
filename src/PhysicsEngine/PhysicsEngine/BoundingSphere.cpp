
#include "PhysicsEngine/BoundingSphere.hpp"
#include "PhysicsEngine/Vector3D.hpp"

namespace engine
{

BoundingSphere::BoundingSphere(const std::vector<std::shared_ptr<RigidBody>>& rigidBodies)
{
    for(auto const& rigidBody: rigidBodies)
    {
        m_rigidBodies.push_back(rigidBody);
    }

    calculateCenter();
    calculateRadius();
}

bool BoundingSphere::collideWith(BoundingSphere& other)
{
    if(m_rigidBodies.size() != 0 && other.m_rigidBodies.size() != 0)
    {
        // calculate distance between the two BoundingSphere' center
        float difX = m_center.getX() - other.m_center.getX();
        float difY = m_center.getY() - other.m_center.getY();
        float difZ = m_center.getZ() - other.m_center.getZ();
        float distance = sqrt(difX * difX + difY * difY + difZ * difZ);

        // if the bounding spheres collide, return true
        if(distance < m_radius + other.m_radius)
        {
            m_isColliding = true;
            other.m_isColliding = true;
        }
    }
    m_isColliding = false;
    other.m_isColliding = false;

    return m_isColliding;
}

void BoundingSphere::calculateCenter()
{
    for(auto const& rigidBody: m_rigidBodies)
    {
        std::shared_ptr<RigidBody> rb = rigidBody.lock();

        m_center += rb->getPosition();
    }
    m_center /= m_rigidBodies.size();
}

void BoundingSphere::calculateRadius()
{
    if(m_rigidBodies.size() != 0)
    {
        std::shared_ptr<RigidBody> rb = m_rigidBodies[0].lock();
        float radius = rb->getGreatestRadius();

        float xMin = rb->getPosition().getX() - radius;
        float yMin = rb->getPosition().getY() - radius;
        float zMin = rb->getPosition().getZ() - radius;
        float xMax = rb->getPosition().getX() + radius;
        float yMax = rb->getPosition().getY() + radius;
        float zMax = rb->getPosition().getZ() + radius;

        for(int i = 1; i < m_rigidBodies.size(); ++i)
        {
            rb = m_rigidBodies[i].lock();
            radius = rb->getGreatestRadius();

            xMin = std::min(xMin, rb->getPosition().getX() - radius);
            yMin = std::min(yMin, rb->getPosition().getY() - radius);
            zMin = std::min(zMin, rb->getPosition().getZ() - radius);
            xMax = std::max(xMax, rb->getPosition().getX() + radius);
            yMax = std::max(yMax, rb->getPosition().getY() + radius);
            zMax = std::max(zMax, rb->getPosition().getZ() + radius);
        }

        float dx = xMax - xMin;
        float dy = yMax - yMin;
        float dz = zMax - zMin;
        m_radius = std::sqrt(dx * dx + dy * dy + dz * dz) / 2;
    }
}

std::vector<std::shared_ptr<RigidBody>> BoundingSphere::getRigidBodies() const
{
    std::vector<std::shared_ptr<RigidBody>> rigidBodies;
    for(auto const& rb: m_rigidBodies)
    {
        rigidBodies.push_back(rb.lock());
    }
    return rigidBodies;
}

} // namespace engine

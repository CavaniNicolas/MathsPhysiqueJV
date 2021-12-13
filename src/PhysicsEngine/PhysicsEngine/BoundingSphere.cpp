#include "PhysicsEngine/BoundingSphere.hpp"

namespace engine
{

BoundingSphere::BoundingSphere(const std::vector<std::shared_ptr<Primitive>>& primitives): BoundingVolume(primitives)
{
    calculateCenter();
    calculateRadius();
}

bool BoundingSphere::collideWith(std::shared_ptr<BoundingVolume>& other)
{
    if(getNumPrimitives() != 0 && other->getNumPrimitives() != 0)
    {
        if (std::shared_ptr<BoundingSphere>& otherBoundingSphere = std::dynamic_pointer_cast<BoundingSphere>(other)) {
            collideWithSphere(otherBoundingSphere);
        }
        else if(std::shared_ptr<BoundingPlan>& otherBoundingPlan = std::dynamic_pointer_cast<BoundingPlan>(other))
        {
            collideWithPlan(otherBoundingPlan);
        }
    }
    else
    {
        m_isColliding = false || m_isColliding;
        other->setColliding(false || other->isColliding());
    }

    return m_isColliding;
}

bool BoundingSphere::collideWithSphere(std::shared_ptr<BoundingSphere>& otherBoundingSphere) {
    // calculate distance between the two BoundingSphere' center
    Vector3D otherCenter = otherBoundingSphere->getCenter();
    float difX = m_center.getX() - otherCenter.getX();
    float difY = m_center.getY() - otherCenter.getY();
    float difZ = m_center.getZ() - otherCenter.getZ();
    float distance = sqrt(difX * difX + difY * difY + difZ * difZ);

    // if the bounding spheres collide, return true
    if(distance < m_radius + otherBoundingSphere->getRadius())
    {
        m_isColliding = true;
        otherBoundingSphere->setColliding(true);
        return true;
    }
    else
    {
        m_isColliding = false || m_isColliding;
        otherBoundingSphere->setColliding(false || otherBoundingSphere->isColliding());
        return false;
    }
}

bool BoundingSphere::collideWithPlan(std::shared_ptr<BoundingPlan>& otherBoundingPlan) {
    float yMinHeight = m_center.getY() - m_radius;

    if (yMinHeight <= otherBoundingPlan->getHeight()) {
        m_isColliding = true;
        otherBoundingPlan->setColliding(true);
        return true;
    }
    else
    {
        m_isColliding = false || m_isColliding;
        otherBoundingPlan->setColliding(false || otherBoundingPlan->isColliding());
        return false;
    }
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

} // namespace engine

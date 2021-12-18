#include "PhysicsEngine/BoundingSphere.hpp"
#include "PhysicsEngine/Box.hpp"

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
        if(std::shared_ptr<BoundingSphere>& otherBoundingSphere = std::dynamic_pointer_cast<BoundingSphere>(other))
        {
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

bool BoundingSphere::collideWithSphere(std::shared_ptr<BoundingSphere>& otherBoundingSphere)
{
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

bool BoundingSphere::collideWithPlan(std::shared_ptr<BoundingPlan>& otherBoundingPlan)
{
    float yMinHeight = m_center.getY() - m_radius;

    if(yMinHeight <= otherBoundingPlan->getHeight())
    {
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
    for(auto const& primitive: m_primitives)
    {
        std::shared_ptr<Primitive> prim = primitive.lock();

        m_center += prim->getPosition();
    }
    m_center /= m_primitives.size();
}

void BoundingSphere::calculateRadius()
{
    if(m_primitives.size() != 0)
    {
        std::shared_ptr<Primitive> prim = m_primitives[0].lock();
        float radius = 0;
        if(std::shared_ptr<Box> box = std::dynamic_pointer_cast<Box>(prim))
        {
            radius = box->getGreatestHalfSize();
        }

        float xMin = prim->getPosition().getX() - radius;
        float yMin = prim->getPosition().getY() - radius;
        float zMin = prim->getPosition().getZ() - radius;
        float xMax = prim->getPosition().getX() + radius;
        float yMax = prim->getPosition().getY() + radius;
        float zMax = prim->getPosition().getZ() + radius;

        for(int i = 1; i < m_primitives.size(); ++i)
        {
            prim = m_primitives[i].lock();
            radius = 0;
            if(std::shared_ptr<Box> box = std::dynamic_pointer_cast<Box>(prim))
            {
                radius = box->getGreatestHalfSize();
            }

            xMin = std::min(xMin, prim->getPosition().getX() - radius);
            yMin = std::min(yMin, prim->getPosition().getY() - radius);
            zMin = std::min(zMin, prim->getPosition().getZ() - radius);
            xMax = std::max(xMax, prim->getPosition().getX() + radius);
            yMax = std::max(yMax, prim->getPosition().getY() + radius);
            zMax = std::max(zMax, prim->getPosition().getZ() + radius);
        }

        float dx = xMax - xMin;
        float dy = yMax - yMin;
        float dz = zMax - zMin;
        m_radius = std::sqrt(dx * dx + dy * dy + dz * dz) / 2;
    }
}

} // namespace engine

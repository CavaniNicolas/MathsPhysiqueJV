#include "PhysicsEngine/Box.hpp"
#include "PhysicsEngine/Plan.hpp"

namespace engine
{
Box::Box(std::shared_ptr<RigidBody> body, Matrix34 offset, Vector3D halfSizes):
  Primitive(body, offset), m_halfSizes(halfSizes)
{
}

Vector3D Box::getHalfSizes() const
{
    return m_halfSizes;
}

void Box::setHalfSizes(Vector3D halfSizes)
{
    m_halfSizes = halfSizes;
}

float Box::getGreatestHalfSize() const
{
    float greatestHalfSize = std::max(m_halfSizes.getX(), m_halfSizes.getY());
    return std::max(greatestHalfSize, m_halfSizes.getZ());
}

std::vector<Vector3D> Box::getApexes() const {
    Vector3D selfPosition = getPosition();
    float dx = m_halfSizes.getX();
    float dy = m_halfSizes.getY();
    float dz = m_halfSizes.getZ();
    std::vector<Vector3D> ret;
    ret.push_back(selfPosition + Vector3D(dx, dy, dz));
    ret.push_back(selfPosition + Vector3D(dx, dy, -dz));
    ret.push_back(selfPosition + Vector3D(dx, -dy, dz));
    ret.push_back(selfPosition + Vector3D(dx, -dy, -dz));
    ret.push_back(selfPosition + Vector3D(-dx, dy, dz));
    ret.push_back(selfPosition + Vector3D(-dx, dy, -dz));
    ret.push_back(selfPosition + Vector3D(-dx, -dy, dz));
    ret.push_back(selfPosition + Vector3D(-dx, -dy, -dz));

    return ret;
}

float Box::getYMax() const {
    float yMax = getPosition().getY() + m_halfSizes.getNorm();
    return yMax;
}

void Box::generateContactWith(const std::shared_ptr<Primitive>& other, RigidBodyCollisionData& collisionData) {
    std::vector<Vector3D> apexes = getApexes();
    if (const std::shared_ptr<Plan>& plan = std::dynamic_pointer_cast<Plan>(other)) {
        for(Vector3D& apex: apexes)
        {
            if(plan->getNormal().scalarProduct(apex) <= -plan->getPlanOffset())
            {
                float penetrationDistance = std::abs(plan->getPlanOffset() - apex.getY());
                Vector3D contactPoint = Vector3D(apex.getX(), plan->getPlanOffset(), apex.getZ());
                RigidBodyContact currentContact =
                  RigidBodyContact(contactPoint, plan->getNormal(), penetrationDistance);
                collisionData.addContact(currentContact);
            }
        }
    }
}
} // namespace engine
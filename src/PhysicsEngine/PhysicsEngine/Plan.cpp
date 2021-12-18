#include "PhysicsEngine/Plan.hpp"
#include "PhysicsEngine/Box.hpp"

namespace engine
{
Plan::Plan(Vector3D normal, float planOffset):
  Primitive(nullptr, Matrix34()), m_normal(normal), m_planOffset(planOffset)
{
}

Vector3D Plan::getNormal() const
{
    return m_normal;
}
float Plan::getPlanOffset() const
{
    return m_planOffset;
}

void Plan::setNormal(Vector3D normal)
{
    m_normal = normal;
}
void Plan::setPlanOffset(float planOffset)
{
    m_planOffset = planOffset;
}

float Plan::getYMax() const
{
    return m_planOffset;
}

void Plan::generateContactWith(const std::shared_ptr<Primitive>& other, RigidBodyCollisionData& collisionData)
{
    if(const std::shared_ptr<Box>& box = std::dynamic_pointer_cast<Box>(other))
    {
        box->generateContactWith(shared_from_this(), collisionData);
    }
}
} // namespace engine
#include <memory>

#include "PhysicsEngine/BoundingPlan.hpp"
#include "PhysicsEngine/BoundingSphere.hpp"

namespace engine
{
BoundingPlan::BoundingPlan(float height, const std::vector<std::shared_ptr<Primitive>>& primitives):
  BoundingVolume(primitives), m_height(height)
{
}

bool BoundingPlan::collideWith(std::shared_ptr<BoundingVolume>& other)
{
    if(std::shared_ptr<BoundingSphere>& otherBoundingSphere = std::dynamic_pointer_cast<BoundingSphere>(other))
    {
        return otherBoundingSphere->collideWithPlan(shared_from_this());
    }
    else
    {
        m_isColliding = false || m_isColliding;
        other->setColliding(false || other->isColliding());
        return false;
    }
}
} // namespace engine
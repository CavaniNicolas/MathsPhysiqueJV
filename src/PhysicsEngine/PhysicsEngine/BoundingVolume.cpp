#include "PhysicsEngine/BoundingVolume.hpp"

namespace engine
{
BoundingVolume::BoundingVolume(const std::vector<std::shared_ptr<Primitive>>& primitives): m_isColliding(false)
{
    for(auto const& primitive: primitives)
    {
        m_primitives.push_back(primitive);
    }
}

std::vector<std::shared_ptr<Primitive>> BoundingVolume::getPrimitives() const
{
    std::vector<std::shared_ptr<Primitive>> primitives;
    for(auto const& primitive: m_primitives)
    {
        primitives.push_back(primitive.lock());
    }
    return primitives;
}
} // namespace engine
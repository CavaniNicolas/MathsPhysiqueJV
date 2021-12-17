#pragma once

#include <vector>
#include <memory>
#include "PhysicsEngine/Primitive.hpp"

namespace engine
{
class BoundingVolume
{
  protected:
    std::vector<std::weak_ptr<Primitive>> m_primitives;

    bool m_isColliding;

  public:
    BoundingVolume(const std::vector<std::shared_ptr<Primitive>>& primitives = {});

    virtual bool collideWith(std::shared_ptr<BoundingVolume>& other) = 0;

    std::vector<std::shared_ptr<Primitive>> getPrimitives() const;

    inline bool isColliding() const
    {
        return m_isColliding;
    }

    inline void setColliding(bool colliding)
    {
        m_isColliding = colliding;
    }

    inline int getNumPrimitives() const
    {
        return m_primitives.size();
    }
};
} // namespace engine

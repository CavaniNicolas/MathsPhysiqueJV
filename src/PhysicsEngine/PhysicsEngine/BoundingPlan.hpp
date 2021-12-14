#pragma once

#include "PhysicsEngine/BoundingVolume.hpp"

namespace engine
{
class BoundingPlan
  : public BoundingVolume
  , public std::enable_shared_from_this<BoundingPlan>
{
  private:
    float m_height;

  public:
    BoundingPlan(float height, const std::vector<std::shared_ptr<Primitive>>& primitives = {});

    virtual bool collideWith(std::shared_ptr<BoundingVolume>& other);

    inline float getHeight() const
    {
        return m_height;
    }
};
} // namespace engine

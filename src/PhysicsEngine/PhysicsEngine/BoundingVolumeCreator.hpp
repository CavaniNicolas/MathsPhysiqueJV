#pragma once

#include "PhysicsEngine/BoundingSphere.hpp"
#include "PhysicsEngine/BoundingPlan.hpp"

namespace engine
{
class BoundingVolumeCreator
{
  private:
    bool containsPlan(const std::vector<std::shared_ptr<Primitive>>& primitives);

  public:
    std::shared_ptr<BoundingVolume> createBoundingVolume(const std::vector<std::shared_ptr<Primitive>>& primitives);
};
} // namespace engine
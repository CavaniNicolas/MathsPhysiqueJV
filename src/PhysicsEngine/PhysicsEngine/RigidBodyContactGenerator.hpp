#pragma once

#include "PhysicsEngine/RigidBodyCollisionData.hpp"
#include "PhysicsEngine/Primitive.hpp"

namespace engine
{
class RigidBodyContactGenerator
{
  public:
    void generateContact(const std::shared_ptr<Primitive>& prim1,
                         const std::shared_ptr<Primitive>& prim2,
                         RigidBodyCollisionData& collisionData);
};
} // namespace engine
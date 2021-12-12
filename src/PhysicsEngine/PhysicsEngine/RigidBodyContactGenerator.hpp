#pragma once

#include "PhysicsEngine/RigidBodyCollisionData.hpp"
#include "PhysicsEngine/Primitive.hpp"

namespace engine
{
class RigidBodyContactGenerator
{
  public:
    void generateContact(std::shared_ptr<Primitive> prim1,
                         std::shared_ptr<Primitive> prim2,
                         RigidBodyCollisionData& collisionDatas);
};
} // namespace engine
#pragma once

#include <vector>
#include <utility>
#include "PhysicsEngine/BoundingSphere.hpp"

namespace engine
{
enum Type
{
    LEAF,
    NODE
};

struct Node
{
    Type type;
    BoundingSphere boundingVolume;
    std::unique_ptr<BVH> m_leftTree;
    std::unique_ptr<BVH> m_rightTree;
};

class BVH
{
  private:
    Node m_root;

  public:
    BVH(std::vector<std::shared_ptr<PhysicsObject>>& objects);

    std::vector<std::pair<std::weak_ptr<RigidBody>, std::weak_ptr<RigidBody>>> getPossibleCollisions();
};
} // namespace engine
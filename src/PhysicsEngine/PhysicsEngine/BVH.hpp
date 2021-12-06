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

struct Node;

class BVH
{
  private:
    std::shared_ptr<Node> m_root;

    std::pair<std::vector<std::shared_ptr<RigidBody>>, std::vector<std::shared_ptr<RigidBody>>> partitionObjects(
      const std::vector<std::shared_ptr<RigidBody>>& rigidBodies);

    void createBVH(const std::vector<std::shared_ptr<RigidBody>>& rigidBodies);

  public:
    BVH(std::vector<std::shared_ptr<PhysicsObject>>& objects);
    BVH(std::vector<std::shared_ptr<RigidBody>>& rigidBodies);

    std::vector<std::pair<std::weak_ptr<RigidBody>, std::weak_ptr<RigidBody>>> getPossibleCollisions(
      std::shared_ptr<BVH> toEvaluate = nullptr);
};

struct Node
{
    Type type;
    BoundingSphere boundingVolume;
    std::shared_ptr<BVH> m_leftTree;
    std::shared_ptr<BVH> m_rightTree;

    Node(const std::vector<std::shared_ptr<RigidBody>>& rigidBodies)
    {
        type = LEAF;
        boundingVolume = BoundingSphere(rigidBodies);
        m_leftTree = nullptr;
        m_rightTree = nullptr;
    }
};
} // namespace engine

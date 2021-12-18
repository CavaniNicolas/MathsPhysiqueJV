#pragma once

#include <vector>
#include <utility>
#include "PhysicsEngine/BoundingVolumeCreator.hpp"

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

    std::pair<std::vector<std::shared_ptr<Primitive>>, std::vector<std::shared_ptr<Primitive>>> partitionObjects(
      const std::vector<std::shared_ptr<Primitive>>& primitives);

    void createBVH(const std::vector<std::shared_ptr<Primitive>>& primitives);

  public:
    BVH(const std::vector<std::shared_ptr<Primitive>>& primitives);

    std::vector<std::pair<std::shared_ptr<Primitive>, std::shared_ptr<Primitive>>> getPossibleCollisions(
      std::shared_ptr<BVH> toEvaluate = nullptr);

    std::vector<std::shared_ptr<BoundingVolume>> getBoundingVolumes() const;
};

struct Node
{
    Type m_type;
    std::shared_ptr<BoundingVolume> m_boundingVolume;
    std::shared_ptr<BVH> m_leftTree;
    std::shared_ptr<BVH> m_rightTree;

    Node(const std::vector<std::shared_ptr<Primitive>>& primitives)
    {
        m_type = LEAF;
        BoundingVolumeCreator boundingVolumeCreator = BoundingVolumeCreator();
        m_boundingVolume = boundingVolumeCreator.createBoundingVolume(primitives);
        m_leftTree = nullptr;
        m_rightTree = nullptr;
    }
};
} // namespace engine

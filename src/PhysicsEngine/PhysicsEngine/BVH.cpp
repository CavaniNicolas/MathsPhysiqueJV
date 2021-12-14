#include "PhysicsEngine/BVH.hpp"

namespace engine
{
BVH::BVH(const std::vector<std::shared_ptr<Primitive>>& primitives)
{
    createBVH(primitives);
}

void BVH::createBVH(const std::vector<std::shared_ptr<Primitive>>& primitives)
{
    int numObjects = primitives.size();
    if(numObjects > 0)
    {
        const int MIN_OBJECTS_PER_LEAF = 1;

        m_root = std::make_shared<Node>(primitives);

        // rigidBodies.size() (numObjects) must be 2 or more, or it will crash
        if(numObjects > MIN_OBJECTS_PER_LEAF)
        {
            m_root->m_type = NODE;

            auto partitions = partitionObjects(primitives);

            m_root->m_leftTree = std::make_shared<BVH>(partitions.first);
            m_root->m_rightTree = std::make_shared<BVH>(partitions.second);
        }
    }
}

// rigidBodies.size() must be 2 or more, or it will crash
std::pair<std::vector<std::shared_ptr<Primitive>>, std::vector<std::shared_ptr<Primitive>>> BVH::partitionObjects(
  const std::vector<std::shared_ptr<Primitive>>& primitives)
{
    std::pair<std::vector<std::shared_ptr<Primitive>>, std::vector<std::shared_ptr<Primitive>>> ret;

    std::shared_ptr<Primitive> firstFarthest;
    std::shared_ptr<Primitive> secondFarthest;

    // We find the two farthest objects
    for(int i = 0; i < primitives.size(); i++)
    {
        if(firstFarthest == nullptr)
        {
            firstFarthest = primitives[i];
        }
        for(int j = i + 1; j < primitives.size(); j++)
        {
            if(secondFarthest == nullptr)
            {
                secondFarthest = primitives[j];
            }
            else if(Vector3D::squareDistance(primitives[i]->getPosition(), primitives[j]->getPosition()) >
                    Vector3D::squareDistance(firstFarthest->getPosition(), secondFarthest->getPosition()))
            {
                firstFarthest = primitives[i];
                secondFarthest = primitives[j];
            }
        }
    }

    // We find which object is closer to the first one, and which is closer to the second one
    // This will form our two partitions
    for(int i = 0; i < primitives.size(); i++)
    {
        float distanceWithFirst = Vector3D::squareDistance(primitives[i]->getPosition(), firstFarthest->getPosition());
        float distanceWithSecond =
          Vector3D::squareDistance(primitives[i]->getPosition(), secondFarthest->getPosition());
        if(distanceWithFirst < distanceWithSecond)
        {
            ret.first.push_back(primitives[i]);
        }
        else
        {
            ret.second.push_back(primitives[i]);
        }
    }

    return ret;
}

std::vector<std::pair<std::shared_ptr<Primitive>, std::shared_ptr<Primitive>>> BVH::getPossibleCollisions(
  std::shared_ptr<BVH> toEvaluate)
{
    std::vector<std::pair<std::shared_ptr<Primitive>, std::shared_ptr<Primitive>>> ret;
    if(toEvaluate == nullptr)
    {
        if(m_root->m_type == NODE)
        {
            if(m_root->m_leftTree->m_root->m_type == LEAF && m_root->m_rightTree->m_root->m_type == LEAF)
            {
                ret = m_root->m_leftTree->getPossibleCollisions(m_root->m_rightTree);
            }
            else if(m_root->m_leftTree->m_root->m_type == LEAF && m_root->m_rightTree->m_root->m_type == NODE)
            {
                ret = m_root->m_rightTree->getPossibleCollisions(m_root->m_leftTree);
            }
            else if(m_root->m_leftTree->m_root->m_type == NODE && m_root->m_rightTree->m_root->m_type == LEAF)
            {
                ret = m_root->m_leftTree->getPossibleCollisions(m_root->m_rightTree);
            }
            else
            {
                std::vector<std::pair<std::shared_ptr<Primitive>, std::shared_ptr<Primitive>>> retLeft =
                  m_root->m_leftTree->getPossibleCollisions();
                std::vector<std::pair<std::shared_ptr<Primitive>, std::shared_ptr<Primitive>>> retRight =
                  m_root->m_rightTree->getPossibleCollisions();
                ret.reserve(retLeft.size() + retRight.size()); // preallocate memory
                ret.insert(ret.end(), retLeft.begin(), retLeft.end());
                ret.insert(ret.end(), retRight.begin(), retRight.end());
            }
        }
    }
    else
    {
        if(m_root->m_boundingVolume->collideWith(toEvaluate->m_root->m_boundingVolume))
        {
            if(m_root->m_type == LEAF)
            {
                ret.push_back({toEvaluate->m_root->m_boundingVolume->getPrimitives()[0],
                               m_root->m_boundingVolume->getPrimitives()[0]});
            }
            else
            {
                std::vector<std::pair<std::shared_ptr<Primitive>, std::shared_ptr<Primitive>>> retLeft =
                  m_root->m_leftTree->getPossibleCollisions(toEvaluate);
                std::vector<std::pair<std::shared_ptr<Primitive>, std::shared_ptr<Primitive>>> retRight =
                  m_root->m_rightTree->getPossibleCollisions(toEvaluate);
                ret.reserve(retLeft.size() + retRight.size()); // preallocate memory
                ret.insert(ret.end(), retLeft.begin(), retLeft.end());
                ret.insert(ret.end(), retRight.begin(), retRight.end());
            }
        }
        else
        {
            ret = getPossibleCollisions();
        }
    }

    return ret;
}

std::vector<std::shared_ptr<BoundingVolume>> BVH::getBoundingVolumes() const
{
    std::vector<std::shared_ptr<BoundingVolume>> volumes;
    volumes.push_back(m_root->m_boundingVolume);
    if(m_root->m_type == NODE)
    {
        std::vector<std::shared_ptr<BoundingVolume>> leftVolumes = m_root->m_leftTree->getBoundingVolumes();
        std::vector<std::shared_ptr<BoundingVolume>> rightVolumes = m_root->m_rightTree->getBoundingVolumes();
        volumes.reserve(volumes.size() + leftVolumes.size() + rightVolumes.size()); // preallocate memory
        volumes.insert(volumes.end(), leftVolumes.begin(), leftVolumes.end());
        volumes.insert(volumes.end(), rightVolumes.begin(), rightVolumes.end());
    }
    return volumes;
}
} // namespace engine
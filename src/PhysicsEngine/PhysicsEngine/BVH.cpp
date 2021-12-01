#include "PhysicsEngine/BVH.hpp"

using namespace engine;

BVH::BVH(std::vector<std::shared_ptr<PhysicsObject>>& objects)
{
    std::vector<std::shared_ptr<RigidBody>> rigidBodies;

    for(std::shared_ptr<PhysicsObject> physicsObject: objects)
    {
        if(std::shared_ptr<RigidBody> rigidBody = std::dynamic_pointer_cast<RigidBody>(physicsObject))
        {
            rigidBodies.push_back(rigidBody);
        }
    }

    int numObjects = rigidBodies.size();
    if(numObjects > 0)
    {
        const int MIN_OBJECTS_PER_LEAF = 1;

        m_root = std::make_unique<Node>(rigidBodies);

        if(numObjects > MIN_OBJECTS_PER_LEAF)
        {
            m_root->type = NODE;

            auto partitions = partitionObjects(rigidBodies);

            m_root->m_leftTree = std::make_unique<BVH>(partitions.first);
            m_root->m_rightTree = std::make_unique<BVH>(partitions.second);
        }
    }
}

BVH::BVH(std::vector<std::shared_ptr<RigidBody>>& rigidBodies)
{
    int numObjects = rigidBodies.size();
    if(numObjects > 0)
    {
        const int MIN_OBJECTS_PER_LEAF = 1;

        m_root = std::make_unique<Node>(rigidBodies);

        if(numObjects > MIN_OBJECTS_PER_LEAF)
        {
            m_root->type = NODE;

            auto partitions = partitionObjects(rigidBodies);

            m_root->m_leftTree = std::make_unique<BVH>(partitions.first);
            m_root->m_rightTree = std::make_unique<BVH>(partitions.second);
        }
    }
}

std::pair<std::vector<std::shared_ptr<RigidBody>>, std::vector<std::shared_ptr<RigidBody>>> BVH::partitionObjects(
  const std::vector<std::shared_ptr<RigidBody>>& rigidBodies)
{
    std::pair<std::vector<std::shared_ptr<RigidBody>>, std::vector<std::shared_ptr<RigidBody>>> ret;

    std::shared_ptr<RigidBody> firstFarthest;
    std::shared_ptr<RigidBody> secondFarthest;

    // We find the two farthest objects
    for(int i = 0; i < rigidBodies.size(); i++)
    {
        if(firstFarthest == nullptr)
        {
            firstFarthest = rigidBodies[i];
        }
        for(int j = i; j < rigidBodies.size(); j++)
        {
            if(secondFarthest == nullptr)
            {
                secondFarthest = rigidBodies[j];
            }
            else if(Vector3D::squareDistance(rigidBodies[i]->getPosition(), rigidBodies[j]->getPosition()) <
                    Vector3D::squareDistance(firstFarthest->getPosition(), secondFarthest->getPosition()))
            {
                firstFarthest = rigidBodies[i];
                secondFarthest = rigidBodies[j];
            }
        }
    }

    // We find which object is closer to the first one, and which is closer to the second one
    // This will form our two partitions
    for(int i = 0; i < rigidBodies.size(); i++)
    {
        float distanceWithFirst = Vector3D::squareDistance(rigidBodies[i]->getPosition(), firstFarthest->getPosition());
        float distanceWithSecond =
          Vector3D::squareDistance(rigidBodies[i]->getPosition(), secondFarthest->getPosition());
        if(distanceWithFirst < distanceWithSecond)
        {
            ret.first.push_back(rigidBodies[i]);
        }
        else
        {
            ret.second.push_back(rigidBodies[i]);
        }
    }

    return ret;
}

std::vector<std::pair<std::weak_ptr<RigidBody>, std::weak_ptr<RigidBody>>> BVH::getPossibleCollisions()
{
    std::vector<std::pair<std::weak_ptr<RigidBody>, std::weak_ptr<RigidBody>>> ret;
}
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

    createBVH(rigidBodies);
}

BVH::BVH(std::vector<std::shared_ptr<RigidBody>>& rigidBodies)
{
    createBVH(rigidBodies);
}

void BVH::createBVH(const std::vector<std::shared_ptr<RigidBody>>& rigidBodies)
{
    int numObjects = rigidBodies.size();
    if(numObjects > 0)
    {
        const int MIN_OBJECTS_PER_LEAF = 1;

        m_root = std::make_shared<Node>(rigidBodies);

        if(numObjects > MIN_OBJECTS_PER_LEAF)
        {
            m_root->type = NODE;

            auto partitions = partitionObjects(rigidBodies);

            m_root->m_leftTree = std::make_shared<BVH>(partitions.first);
            m_root->m_rightTree = std::make_shared<BVH>(partitions.second);
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

std::vector<std::pair<std::shared_ptr<RigidBody>, std::shared_ptr<RigidBody>>> BVH::getPossibleCollisions(
  std::shared_ptr<BVH> toEvaluate)
{
    std::vector<std::pair<std::shared_ptr<RigidBody>, std::shared_ptr<RigidBody>>> ret;
    if(toEvaluate == nullptr)
    {
        if(m_root->type == NODE)
        {
            if(m_root->m_leftTree->m_root->type == LEAF && m_root->m_rightTree->m_root->type == LEAF)
            {
                ret = m_root->m_leftTree->getPossibleCollisions(m_root->m_rightTree);
            }
            else if(m_root->m_leftTree->m_root->type == LEAF && m_root->m_rightTree->m_root->type == NODE)
            {
                ret = m_root->m_rightTree->getPossibleCollisions(m_root->m_leftTree);
            }
            else if(m_root->m_leftTree->m_root->type == NODE && m_root->m_rightTree->m_root->type == LEAF)
            {
                ret = m_root->m_leftTree->getPossibleCollisions(m_root->m_rightTree);
            }
            else
            {
                std::vector<std::pair<std::shared_ptr<RigidBody>, std::shared_ptr<RigidBody>>> retLeft =
                  m_root->m_leftTree->getPossibleCollisions();
                std::vector<std::pair<std::shared_ptr<RigidBody>, std::shared_ptr<RigidBody>>> retRight =
                  m_root->m_rightTree->getPossibleCollisions();
                ret.reserve(retLeft.size() + retRight.size()); // preallocate memory
                ret.insert(ret.end(), retLeft.begin(), retLeft.end());
                ret.insert(ret.end(), retRight.begin(), retRight.end());
            }
        }
    }
    else
    {
        if(m_root->boundingVolume.collideWith(toEvaluate->m_root->boundingVolume))
        {
            if(m_root->type == LEAF)
            {
                ret.push_back(
                  {toEvaluate->m_root->boundingVolume.getRigidBodies()[0], m_root->boundingVolume.getRigidBodies()[0]});
            }
            else
            {
                std::vector<std::pair<std::shared_ptr<RigidBody>, std::shared_ptr<RigidBody>>> retLeft =
                  m_root->m_leftTree->getPossibleCollisions(toEvaluate);
                std::vector<std::pair<std::shared_ptr<RigidBody>, std::shared_ptr<RigidBody>>> retRight =
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

std::vector<BoundingSphere> BVH::getBoundingSpheres() const
{
    std::vector<BoundingSphere> spheres;
    spheres.push_back(m_root->boundingVolume);
    if(m_root->type == NODE)
    {
        std::vector<BoundingSphere> leftSpheres = m_root->m_leftTree->getBoundingSpheres();
        std::vector<BoundingSphere> rightSpheres = m_root->m_rightTree->getBoundingSpheres();
        spheres.reserve(spheres.size() + leftSpheres.size() + rightSpheres.size()); // preallocate memory
        spheres.insert(spheres.end(), leftSpheres.begin(), leftSpheres.end());
        spheres.insert(spheres.end(), rightSpheres.begin(), rightSpheres.end());
    }
    return spheres;
}

#pragma once

#include <vector>
#include <memory>
#include "PhysicsEngine/RigidBody.hpp"

namespace engine
{
class BoundingSphere
{
  private:
    std::vector<std::weak_ptr<RigidBody>> m_rigidBodies;
    Vector3D m_center;
    float m_radius;

  public:
    BoundingSphere(const std::vector<std::shared_ptr<RigidBody>>& rigidBodies = {});

    bool collideWith(const BoundingSphere& other) const;

    std::vector<std::shared_ptr<RigidBody>> getRigidBodies();

    int getNumObjects();
};
} // namespace engine

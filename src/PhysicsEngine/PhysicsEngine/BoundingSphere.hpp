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

    bool m_isColliding;

  public:
    BoundingSphere(const std::vector<std::shared_ptr<RigidBody>>& rigidBodies = {});

    bool collideWith(BoundingSphere& other);

    std::vector<std::shared_ptr<RigidBody>> getRigidBodies();

    void calculateCenter();
    void calculateRadius();

    inline int getNumObjects() const
    {
        return m_rigidBodies.size();
    }
};
} // namespace engine

#pragma once

#include <memory>
#include "PhysicsEngine/RigidBody.hpp"

namespace engine
{
class BoundingSphere
{
  private:
    std::weak_ptr<RigidBody> m_rigidBody;
    float m_radius;

  public:
    bool collideWith(const BoundingSphere& other) const;

    std::shared_ptr<RigidBody> getRigidBody();
};
} // namespace engine

#pragma once

#include "PhysicsEngine/Projectile.hpp"

namespace engine
{

class Bullet : public Projectile
{
  public:
    Bullet();

    Bullet(Vector3D initialPosition, Vector3D direction, float damage, float radius, float damping = 0.999);

    Bullet(const Bullet& other);
};

} // namespace engine

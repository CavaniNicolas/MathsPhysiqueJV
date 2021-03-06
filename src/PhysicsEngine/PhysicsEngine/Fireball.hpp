#pragma once

#include "PhysicsEngine/Projectile.hpp"

namespace engine
{

class Fireball : public Projectile
{
  public:
    Fireball();

    Fireball(Vector3D initialPosition, Vector3D direction, float damage, float radius, float damping = 0.999);

    Fireball(const Fireball& other);
};

} // namespace engine

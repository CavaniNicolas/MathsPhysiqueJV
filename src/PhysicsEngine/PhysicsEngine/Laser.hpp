#pragma once

#include "PhysicsEngine/Projectile.hpp"

namespace engine
{

class Laser : public Projectile
{
  public:
    Laser(float damage, float radius, float speedFactor);
    Laser();
    Laser(Vector3D initialPosition, Vector3D direction, float damage, float radius, float damping = 0.999);

    Laser(const Laser& other);
};

} // namespace engine

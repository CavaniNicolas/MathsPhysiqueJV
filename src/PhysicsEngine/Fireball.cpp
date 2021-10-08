#include "Fireball.hpp"

Fireball::Fireball(): Projectile()
{
    setSpeedFactor(30);
    setMass(1);
    setG(-10);
}

Fireball::Fireball(Vector3D initialPosition, Vector3D direction, float damage, float radius, float damping):
  Projectile(initialPosition, direction, 30, 1, damage, radius, -10, damping)
{
}

Fireball::Fireball(const Fireball& other):
  Fireball(other.getPosition(), other.getDirection(), other.getDamage(), other.getRadius(), other.getDamping())
{
}
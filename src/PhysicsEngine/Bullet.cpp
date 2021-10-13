
#include "Bullet.hpp"

Bullet::Bullet(): Projectile()
{
    setSpeedFactor(40);
    setMass(5);
    setG(15);
}

Bullet::Bullet(Vector3D initialPosition, Vector3D direction, float damage, float radius, float damping):
  Projectile(initialPosition, direction, 40, 1, damage, radius, 15, damping)
{
}

Bullet::Bullet(const Bullet& other):
  Bullet(other.getPosition(), other.getDirection(), other.getDamage(), other.getRadius(), other.getDamping())
{
}

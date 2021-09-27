
#include "Laser.hpp"

Laser::Laser():
    Projectile::Projectile()
{
	setSpeedFactor(100);
	setMass(1);
	setG(0);
}

Laser::Laser(Vector3D initialPosition, Vector3D direction,
    float damage, float radius, float damping):
    Projectile::Projectile(initialPosition, direction, 100, 1, damage, radius, 0, damping)
{}

Laser::Laser(const Laser& other):
    Laser::Laser(other.getPosition(), other.getDirection(), other.getDamage(), other.getRadius(), other.getDamping())
{}

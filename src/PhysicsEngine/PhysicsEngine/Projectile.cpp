
#include "PhysicsEngine/Projectile.hpp"

Projectile::Projectile(float damage, float speedFactor):
  Particle(), m_damage(damage), m_speedFactor(speedFactor)
{
}

Projectile::Projectile(): Particle(), m_damage(0), m_speedFactor(1) {}

Projectile::Projectile(Vector3D initialPosition,
                       Vector3D direction,
                       float speedFactor,
                       float mass,
                       float damage,
                       float radius,
                       float g,
                       float damping):
  Particle::Particle(initialPosition, Vector3D(direction.normalize() * speedFactor), radius, mass, g, damping),
  m_speedFactor(speedFactor),
  m_damage(damage),
  m_direction(direction)
{
}

Projectile::Projectile(const Projectile& other):
  Projectile::Projectile(other.getPosition(),
                         other.getDirection(),
                         other.getSpeedFactor(),
                         other.getMass(),
                         other.getDamage(),
                         other.getRadius(),
                         other.getG(),
                         other.getDamping())
{
}

float Projectile::getDamage() const
{
    return m_damage;
}

Vector3D Projectile::getDirection() const
{
    return m_direction;
}

float Projectile::getSpeedFactor() const
{
    return m_speedFactor;
}

void Projectile::setDamage(float damage)
{
    m_damage = damage;
}

void Projectile::setDirection(Vector3D direction)
{
    m_direction = direction;
    setVelocity(direction.normalize() * m_speedFactor);
}

void Projectile::setSpeedFactor(float speedFactor)
{
    m_speedFactor = speedFactor;

    setVelocity(m_direction.normalize() * m_speedFactor);
}

#include "../headers/Projectile.hpp"

Projectile::Projectile() : Particle() {
	m_damage = 0;
	m_radius = 1;
	m_speedFactor = 1;
}

Projectile::Projectile(Vector3D initialPosition, Vector3D direction, float speedFactor, float mass,
	float damage, float radius, float g, float damping) :
	Particle(initialPosition, Vector3D(), { direction.normalize() * speedFactor }, mass, g, damping)
{
	m_speedFactor = speedFactor;
	m_damage = damage;
	m_direction = direction;
	m_radius = radius;
}


Projectile::Projectile(const Projectile& other) : 
	Projectile(other.getPosition(), other.getDirection(), other.getSpeedFactor(), other.getMass(), other.getDamage(), other.getRadius(), other.getG(), other.getDamping()) 
{ }

float Projectile::getDamage() const {
	return m_damage;
}

float Projectile::getRadius() const {
	return m_radius;
}

Vector3D Projectile::getDirection() const {
	return m_direction;
}

float Projectile::getSpeedFactor() const {
	return m_speedFactor;
}

void Projectile::setDamage(float damage) {
	m_damage = damage;
}

void Projectile::setRadius(float radius) {
	m_radius = radius;
}

void Projectile::setDirection(Vector3D direction) {
	m_direction = direction;
	setForces({ direction.normalize() * m_speedFactor });

}

void Projectile::setSpeedFactor(float speedFactor) {
	m_speedFactor = speedFactor;

	setForces({ m_direction.normalize() * m_speedFactor });
}
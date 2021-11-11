
#include <cmath>

#include "PhysicsEngine/Particle.hpp"

namespace engine
{
// Constructors
Particle::Particle(Vector3D position, Vector3D velocity, float radius, float mass, float g, float damping):
  PhysicsObject(position, velocity, mass, g, damping), m_radius(radius)
{
}

Particle::Particle(): PhysicsObject() {}

Particle::Particle(const Particle& other):
  Particle(
    other.getPosition(), other.getVelocity(), other.getRadius(), other.getMass(), other.getG(), other.getDamping())
{
}

// Assignation
Particle& Particle::operator=(const Particle& other)
{
    if(this != &other)
    {
        m_radius = other.m_radius;
        setPosition(other.getPosition());
        setVelocity(other.getVelocity());
        setAcceleration(other.getAcceleration());
        setInverseMass(other.getInverseMass());
        setG(other.getG());
        setDamping(other.getDamping());
        setResting(other.isResting());
    }
    return *this;
}

float Particle::getRadius() const
{
    return m_radius;
}

void Particle::setRadius(float radius)
{
    m_radius = radius;
}

float Particle::calculateVolume()
{
    return (4 / 3) * M_PI * std::pow(m_radius, 3);
}

void Particle::integratePosition(float deltaT)
{
    setPosition(getPosition() + getVelocity() * deltaT + getAcceleration() * 0.5 * pow(deltaT, 2));
    // set acceleration to (0,0,0)
    setAcceleration(Vector3D());
}

void Particle::integrateVelocity(float deltaT)
{
    setVelocity(getVelocity() * pow(getDamping(), deltaT));
    setVelocity(getVelocity() + getAcceleration() * deltaT);
    setDeltaT(deltaT);
}

std::ostream& operator<<(std::ostream& out, Particle const& particle)
{
    out << "Position : " << particle.getPosition() << ", "
        << "Velocity : " << particle.getVelocity() << std::endl;
    return out;
}

} // namespace engine

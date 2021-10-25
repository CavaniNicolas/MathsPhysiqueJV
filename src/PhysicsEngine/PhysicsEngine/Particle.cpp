
#include <cmath>

#include "PhysicsEngine/Particle.hpp"

//// Constructors
Particle::Particle(Vector3D position, Vector3D velocity, float radius, float mass, float g, float damping):
  m_radius(radius),
  m_position(position),
  m_velocity(velocity),
  m_acceleration(Vector3D()),
  m_inverseMass(1 / mass),
  m_g(g),
  m_damping(damping),
  m_resting(false)
{
}

Particle::Particle(): Particle::Particle(Vector3D(), Vector3D()) {}

Particle::Particle(const Particle& other):
  Particle::Particle(
    other.m_position, other.m_velocity, other.getRadius(), other.getMass(), other.getG(), other.m_damping)
{
}

// Assignation
Particle& Particle::operator=(const Particle& other)
{
    if(this != &other)
    {
        m_radius = other.m_radius;
        m_position = other.m_position;
        m_velocity = other.m_velocity;
        m_acceleration = other.m_acceleration;
        m_inverseMass = other.m_inverseMass;
        m_g = other.m_g;
        m_damping = other.m_damping;
        m_resting = other.m_resting;
    }
    return *this;
}

float Particle::getInverseMass() const
{
    return m_inverseMass;
}

float Particle::getMass() const
{
    return 1 / m_inverseMass;
}

float Particle::getG() const
{
    return m_g;
}

float Particle::getDamping() const
{
    return m_damping;
}

Vector3D Particle::getPosition() const
{
    return m_position;
}

Vector3D Particle::getVelocity() const
{
    return m_velocity;
}

Vector3D Particle::getAcceleration() const
{
    return m_acceleration;
}

float Particle::getDeltaT() const
{
    return m_deltaT;
}

float Particle::getRadius() const
{
    return m_radius;
}

bool Particle::isResting() const
{
    return m_resting;
}

void Particle::setInverseMass(float inverseMass)
{
    m_inverseMass = inverseMass;
}

void Particle::setMass(float mass)
{
    m_inverseMass = 1 / mass;
}

void Particle::setG(float g)
{
    m_g = g;
}

void Particle::setDamping(float damping)
{
    m_damping = damping;
}

void Particle::setPosition(Vector3D position)
{
    m_position = position;
}

void Particle::setVelocity(Vector3D velocity)
{
    m_velocity = velocity;
}

void Particle::setAcceleration(Vector3D acceleration)
{
    m_acceleration = acceleration;
}

void Particle::setRadius(float radius)
{
    m_radius = radius;
}

void Particle::setResting(bool resting)
{
    m_resting = resting;
}

float Particle::calculateVolume()
{
    return (4 / 3) * M_PI * std::pow(m_radius, 3);
}

void Particle::integratePosition(float deltaT)
{
    m_position += m_velocity * deltaT + m_acceleration * 0.5 * pow(deltaT, 2);
    // set acceleration to (0,0,0)
    setAcceleration(Vector3D());
}

void Particle::integrateVelocity(float deltaT)
{
    m_velocity *= pow(m_damping, deltaT);
    m_velocity += m_acceleration * deltaT;
    m_deltaT = deltaT;
}

std::ostream& operator<<(std::ostream& out, Particle const& particle)
{
    out << "Position : " << particle.m_position << ", "
        << "Velocity : " << particle.m_velocity; // << ", "
                                                 //<< "Acceleration : "	<< particle.m_acceleration	<< ", "
                                                 //<< "Forces : ";
    // for (Vector3D force : particle.m_forces) {
    //	out << force << " ";
    // }
    return out;
}

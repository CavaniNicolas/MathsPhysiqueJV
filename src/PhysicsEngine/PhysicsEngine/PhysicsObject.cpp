#include "PhysicsEngine/PhysicsObject.hpp"

using namespace engine;

// Constructors
PhysicsObject::PhysicsObject(Vector3D position, Vector3D velocity, float mass, float g, float damping):
  m_position(position),
  m_velocity(velocity),
  m_acceleration(Vector3D()),
  m_inverseMass(1 / mass),
  m_g(g),
  m_linearDamping(damping),
  m_resting(false)
{
}

PhysicsObject::PhysicsObject(): PhysicsObject(Vector3D(), Vector3D()) {}

PhysicsObject::PhysicsObject(const PhysicsObject& other):
  PhysicsObject(
    other.m_position, other.m_velocity, other.getMass(), other.m_g, other.m_linearDamping)
{
}

float PhysicsObject::getInverseMass() const
{
    return m_inverseMass;
}

float PhysicsObject::getMass() const
{
    return 1 / m_inverseMass;
}

float PhysicsObject::getG() const
{
    return m_g;
}

float PhysicsObject::getDamping() const
{
    return m_linearDamping;
}

Vector3D PhysicsObject::getPosition() const
{
    return m_position;
}

Vector3D PhysicsObject::getVelocity() const
{
    return m_velocity;
}

Vector3D PhysicsObject::getAcceleration() const
{
    return m_acceleration;
}

float PhysicsObject::getDeltaT() const
{
    return m_deltaT;
}

bool PhysicsObject::isResting() const
{
    return m_resting;
}

void PhysicsObject::setInverseMass(float inverseMass)
{
    m_inverseMass = inverseMass;
}

void PhysicsObject::setMass(float mass)
{
    m_inverseMass = 1 / mass;
}

void PhysicsObject::setG(float g)
{
    m_g = g;
}

void PhysicsObject::setDamping(float damping)
{
    m_linearDamping = damping;
}

void PhysicsObject::setPosition(Vector3D position)
{
    m_position = position;
}

void PhysicsObject::setVelocity(Vector3D velocity)
{
    m_velocity = velocity;
}

void PhysicsObject::setAcceleration(Vector3D acceleration)
{
    m_acceleration = acceleration;
}

void PhysicsObject::setDeltaT(float deltaT) {
    m_deltaT = deltaT;
}

void PhysicsObject::setResting(bool resting)
{
    m_resting = resting;
}
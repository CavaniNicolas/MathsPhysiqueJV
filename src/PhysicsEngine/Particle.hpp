#pragma once

#include <time.h>
#include <vector>

#include "Vector3D.hpp"

class Particle
{
  private:
    float m_inverseMass;
    float m_g;
    float m_damping;

    Vector3D m_position;
    Vector3D m_velocity;
    Vector3D m_acceleration;

  public:
    // Constructors
    Particle(Vector3D position, Vector3D velocity, float mass = 1, float g = 10, float damping = 0.999);
    Particle();
    Particle(const Particle& other);

    // Assignation
    Particle& operator=(const Particle& other);

    float getInverseMass() const;
    float getMass() const;
    float getG() const;
    float getDamping() const;
    Vector3D getPosition() const;
    Vector3D getVelocity() const;
    Vector3D getAcceleration() const;

    void setInverseMass(float inverseMass);
    void setMass(float mass);
    void setG(float g);
    void setDamping(float damping);
    void setPosition(Vector3D position);
    void setVelocity(Vector3D velocity);
    void setAcceleration(Vector3D acceleration);

    virtual void integratePosition(float deltaT);
    virtual void integrateVelocity(float deltaT);

    friend std::ostream& operator<<(std::ostream& out, Particle const& particle);
};

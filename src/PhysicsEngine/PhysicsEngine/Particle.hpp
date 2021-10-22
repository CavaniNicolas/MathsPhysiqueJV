#pragma once

#include <time.h>
#include <vector>

#include "PhysicsEngine/Vector3D.hpp"

#define M_PI 3.14159265358979323846 /* pi */

class Particle
{
  private:
    float m_inverseMass;
    float m_g;
    float m_damping;
    float m_radius;

    Vector3D m_position;
    Vector3D m_velocity;
    Vector3D m_acceleration;

    float m_deltaT;

  public:
    // Constructors
    Particle(Vector3D position, Vector3D velocity, float radius = 1, float mass = 1, float g = 10, float damping = 0.999);
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
    float getDeltaT() const;
    float getRadius() const;

    void setInverseMass(float inverseMass);
    void setMass(float mass);
    void setG(float g);
    void setDamping(float damping);
    void setPosition(Vector3D position);
    void setVelocity(Vector3D velocity);
    void setAcceleration(Vector3D acceleration);
    void setRadius(float radius);

    float calculateVolume();

    virtual void integratePosition(float deltaT);
    virtual void integrateVelocity(float deltaT);

    friend std::ostream& operator<<(std::ostream& out, Particle const& particle);
};

#pragma once

#include "PhysicsEngine/Vector3D.hpp"

namespace engine
{
class PhysicsObject
{
  private:
    // We store inverseMass rather than mass, because we will more often access the
    // inverse mass, and because it allows us to imagine an infinite mass, but not a null mass
    float m_inverseMass;
    // Usefull to prevent the speed from remaining close to 0 without ever reaching it
    float m_linearDamping;
    Vector3D m_position;
    Vector3D m_velocity;
    // Gravity constants
    float m_g;

    // Registers the last delta time between integrations
    float m_deltaT;

    // Tells us if the object is supposed to remain stable in the y axis
    bool m_resting;

    // Acceleration shall be used to update the velocity and the position
    Vector3D m_acceleration;

  public:
    // Constructors
    PhysicsObject(
      Vector3D position, Vector3D velocity, float mass = 1, float g = 10, float damping = 0.999);
    PhysicsObject();
    PhysicsObject(const PhysicsObject& other);

    float getInverseMass() const;
    float getMass() const;
    float getG() const;
    float getDamping() const;
    Vector3D getPosition() const;
    Vector3D getVelocity() const;
    Vector3D getAcceleration() const;
    float getDeltaT() const;
    bool isResting() const;

    void setInverseMass(float inverseMass);
    void setMass(float mass);
    void setG(float g);
    void setDamping(float damping);
    void setPosition(Vector3D position);
    void setVelocity(Vector3D velocity);
    void setAcceleration(Vector3D acceleration);
    void setDeltaT(float deltaT);
    void setResting(bool resting);

    virtual void integratePosition(float deltaT) = 0;
    virtual void integrateVelocity(float deltaT) = 0;
};
} // namespace engine

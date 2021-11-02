#pragma once

#include "PhysicsEngine/Quaternion.hpp"
#include "PhysicsEngine/Matrix34.hpp"

namespace engine
{
class RigidBody
{
  private:
    // same as for Particle
    float m_inverseMass;
    float m_linearDamping;
    Vector3D m_position;
    Vector3D m_velocity;
    float m_g;

    // orientation of the rigid body
    Quaternion m_orientation;

    // angular velocity of the rigid body
    Vector3D m_rotation;

    // calculates transform matrix from orientation and rotation
    Matrix34 m_transformationMatrix;

    // accelerations
    Vector3D m_acceleration;
    Vector3D m_angularAcceleration;

    float m_deltaT;

    // call each frame to calculate the transformMatrix and normalize the orientation
    void calculateDerivedData();

  public:
    RigidBody(Vector3D position,
              Vector3D velocity,
              Quaternion rotation,
              Vector3D angularVelocity,
              float mass = 1,
              float g = 10,
              float damping = 0.999);

    RigidBody();

    RigidBody(const RigidBody& other);

    // Assignation
    RigidBody& operator=(const RigidBody& other);

    // Getters
    float getInverseMass() const;
    float getMass() const;
    float getG() const;
    float getDamping() const;
    Vector3D getPosition() const;
    Vector3D getVelocity() const;
    Vector3D getAcceleration() const;
    Quaternion getOrientation() const;
    Vector3D getRotation() const;
    Vector3D getAngularAcceleration() const;
    float getDeltaT() const;

    // Setters
    void setInverseMass(float inverseMass);
    void setMass(float mass);
    void setG(float g);
    void setDamping(float damping);
    void setPosition(Vector3D position);
    void setVelocity(Vector3D velocity);
    void setAcceleration(Vector3D acceleration);
    void setOrientation(Quaternion orientation);
    void setRotation(Vector3D rotation);
    void setAngularAcceleration(Vector3D angularAcceleration);

    // integrate the rigid body by modifying position, orientation and velocities
    void integratePosition(float deltaT);
    void integrateVelocity(float deltaT);

    friend std::ostream& operator<<(std::ostream& out, RigidBody const& rb);
};
} // namespace engine
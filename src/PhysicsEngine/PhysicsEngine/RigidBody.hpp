#pragma once

#include "PhysicsEngine/PhysicsObject.hpp"
#include "PhysicsEngine/Quaternion.hpp"
#include "PhysicsEngine/Matrix34.hpp"

namespace engine
{
class RigidBody : public PhysicsObject
{
  private:
    // orientation of the rigid body
    Quaternion m_orientation;

    // angular velocity of the rigid body
    Vector3D m_rotation;

    // calculates transform matrix from orientation and rotation
    Matrix34 m_transformationMatrix;

    // accelerations
    Vector3D m_angularAcceleration;

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
    Quaternion getOrientation() const;
    Vector3D getRotation() const;
    Vector3D getAngularAcceleration() const;

    // Setters
    void setOrientation(Quaternion orientation);
    void setRotation(Vector3D rotation);
    void setAngularAcceleration(Vector3D angularAcceleration);

    // integrate the rigid body by modifying position, orientation and velocities
    void integratePosition(float deltaT);
    void integrateVelocity(float deltaT);

    friend std::ostream& operator<<(std::ostream& out, RigidBody const& rb);
};
} // namespace engine
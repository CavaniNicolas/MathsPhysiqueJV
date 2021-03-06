#pragma once

#include "PhysicsEngine/PhysicsObject.hpp"
#include "PhysicsEngine/Quaternion.hpp"
#include "PhysicsEngine/Matrix33.hpp"
#include "PhysicsEngine/Matrix34.hpp"

namespace engine
{
class Primitive;

class RigidBody
  : public PhysicsObject
  , public std::enable_shared_from_this<RigidBody>
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

    // same as linear damping
    // but for rotation
    float m_angularDamping;

    // accumulated force
    // added by ForceGenerator
    Vector3D m_forceAccum;

    // Accumulated torque
    // added by ForceGenerator
    Vector3D m_torqueAccum;

    // The dimensions of the rigidbody
    float m_dx, m_dy, m_dz;

    // The inertia matrix
    Matrix33 m_localInertiaInverseMatrix;
    Matrix33 m_worldInertiaInverseMatrix;

    // call each frame to calculate the transformMatrix and normalize the orientation
    void calculateDerivedData();

    void calculateInertiaMatrix();

  public:
    RigidBody(Vector3D position,
              Vector3D velocity,
              Quaternion rotation,
              Vector3D angularVelocity,
              float dx = 1,
              float dy = 1,
              float dz = 1,
              float mass = 1,
              float g = 10,
              float damping = 0.999,
              float angularDamping = 0.999);

    RigidBody();

    RigidBody(const RigidBody& other);

    // Assignation
    RigidBody& operator=(const RigidBody& other);

    // Getters
    Quaternion getOrientation() const;
    Vector3D getRotation() const;
    Vector3D getAngularAcceleration() const;
    Matrix34 getTransformationMatrix() const;
    float getDx() const;
    float getDy() const;
    float getDz() const;
    Matrix33 getInertiaInverseMatrix() const;

    // Setters
    void setOrientation(Quaternion orientation);
    void setRotation(Vector3D rotation);
    void setAngularAcceleration(Vector3D angularAcceleration);

    // integrate the rigid body by modifying position, orientation and velocities
    void integratePosition(float deltaT);
    void integrateVelocity(float deltaT);

    // Add force on the Center of mass (no torque generated)
    void addForce(const Vector3D& force);

    // Add force at a point in world coordinate
    // Generate force and torque
    void addForceAtPoint(const Vector3D& force, const Vector3D& worldPoint);

    // Add force at a point in local coordinate
    // the point is converted in world coordinate by using the transform matrix
    // Generate torque and force
    void addForceAtBodyPoint(const Vector3D& force, const Vector3D& localPoint);

    // Called each frame to reset m_forceAccum and m_torqueAccum
    void clearAccumulator();

    Vector3D localToWorldCoordinates(Vector3D& coordinates);

    Vector3D getOrientationEuler() const;
    float getGreatestRadius() const;

    friend std::ostream& operator<<(std::ostream& out, RigidBody const& rb);
};
} // namespace engine

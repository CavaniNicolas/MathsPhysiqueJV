#include "PhysicsEngine/RigidBody.hpp"

namespace engine
{
RigidBody::RigidBody(Vector3D position,
                     Vector3D velocity,
                     Quaternion rotation,
                     Vector3D angularVelocity,
                     float mass,
                     float g,
                     float damping):
  m_position(position),
  m_velocity(velocity),
  m_orientation(rotation),
  m_rotation(angularVelocity),
  m_inverseMass(1 / mass),
  m_g(g),
  m_linearDamping(damping)
{
    m_orientation.normalized();
    m_transformationMatrix = Matrix34();
}

// Default
RigidBody::RigidBody(): RigidBody(Vector3D(), Vector3D(), Quaternion(), Vector3D()) {}

// Copy
RigidBody::RigidBody(const RigidBody& other)
{
    if(this != &other)
    {
        m_position = other.m_position;
        m_velocity = other.m_velocity;
        m_acceleration = other.m_acceleration;
        m_inverseMass = other.m_inverseMass;
        m_g = other.m_g;
        m_linearDamping = other.m_linearDamping;
        m_orientation = other.m_orientation;
        m_rotation = other.m_rotation;
        m_angularAcceleration = other.m_angularAcceleration;
    }
}

// Assignation
RigidBody& RigidBody::operator=(const RigidBody& other)
{
    if(this != &other)
    {
        m_position = other.m_position;
        m_velocity = other.m_velocity;
        m_acceleration = other.m_acceleration;
        m_inverseMass = other.m_inverseMass;
        m_g = other.m_g;
        m_linearDamping = other.m_linearDamping;
        m_orientation = other.m_orientation;
        m_rotation = other.m_rotation;
        m_angularAcceleration = other.m_angularAcceleration;
    }
    return *this;
}

// Getters
float RigidBody::getInverseMass() const
{
    return m_inverseMass;
}
float RigidBody::getMass() const
{
    return 1 / m_inverseMass;
}
float RigidBody::getG() const
{
    return m_g;
}
float RigidBody::getDamping() const
{
    return m_linearDamping;
}
Vector3D RigidBody::getPosition() const
{
    return m_position;
}
Vector3D RigidBody::getVelocity() const
{
    return m_velocity;
}
Vector3D RigidBody::getAcceleration() const
{
    return m_acceleration;
}
Quaternion RigidBody::getOrientation() const
{
    return m_orientation;
}
Vector3D RigidBody::getRotation() const
{
    return m_rotation;
}
Vector3D RigidBody::getAngularAcceleration() const
{
    return m_angularAcceleration;
}
float RigidBody::getDeltaT() const
{
    return m_deltaT;
}

// Setters
void RigidBody::setInverseMass(float inverseMass)
{
    m_inverseMass = inverseMass;
}
void RigidBody::setMass(float mass)
{
    m_inverseMass = 1 / mass;
}
void RigidBody::setG(float g)
{
    m_g = g;
}
void RigidBody::setDamping(float damping)
{
    m_linearDamping = damping;
}
void RigidBody::setPosition(Vector3D position)
{
    m_position = position;
}
void RigidBody::setVelocity(Vector3D velocity)
{
    m_velocity = velocity;
}
void RigidBody::setAcceleration(Vector3D acceleration)
{
    m_acceleration = acceleration;
}
void RigidBody::setOrientation(Quaternion orientation)
{
    m_orientation = orientation;
    m_orientation.normalized();
}
void RigidBody::setRotation(Vector3D rotation)
{
    m_rotation = rotation;
}
void RigidBody::setAngularAcceleration(Vector3D angularAcceleration)
{
    m_angularAcceleration = angularAcceleration;
}

// call each frame to calculate the transformMatrix and normalize the orientation
void RigidBody::calculateDerivedData()
{
    m_orientation.normalized();
    m_transformationMatrix.setOrientationAndPosition(m_orientation, m_position);
}

// integrate the rigid body by modifying position, orientation and velocities
void RigidBody::integratePosition(float deltaT)
{
    //We update the transformation matrix
    calculateDerivedData();

    m_transformationMatrix.transformPosition(m_position);
    m_orientation.updateByAngularVelocity(m_rotation, deltaT);

    setAcceleration(Vector3D());
    //Should we reset the angular acceleration as well ?
    //setAngularAcceleration(Vector3D());
}

void RigidBody::integrateVelocity(float deltaT)
{
    m_velocity *= pow(m_linearDamping, deltaT);
    m_velocity += m_acceleration * deltaT;
    m_rotation *= pow(m_linearDamping, deltaT);
    m_rotation += m_angularAcceleration * deltaT;
    m_deltaT = deltaT;
}

std::ostream& operator<<(std::ostream& out, RigidBody const& rb)
{
    out << "Position : " << rb.m_position << ", " << std::endl
        << "Velocity : " << rb.m_velocity << ", " << std::endl
        << "Orientation : " << rb.m_orientation << ", " << std::endl
        << "Rotation : " << rb.m_rotation;
    return out;
}
} // namespace engine
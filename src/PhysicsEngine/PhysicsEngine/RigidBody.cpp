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
  PhysicsObject(position, velocity, mass, g, damping),
  m_orientation(rotation),
  m_rotation(angularVelocity)
{
    m_transformationMatrix = Matrix34();
    calculateDerivedData();
}

// Default
RigidBody::RigidBody(): RigidBody(Vector3D(), Vector3D(), Quaternion(), Vector3D()) {}

// Copy
RigidBody::RigidBody(const RigidBody& other)
{
    if(this != &other)
    {
        setPosition(other.getPosition());
        setVelocity(other.getVelocity());
        setAcceleration(other.getAcceleration());
        setInverseMass(other.getInverseMass());
        setG(other.getG());
        setDamping(other.getDamping());
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
        setPosition(other.getPosition());
        setVelocity(other.getVelocity());
        setAcceleration(other.getAcceleration());
        setInverseMass(other.getInverseMass());
        setG(other.getG());
        setDamping(other.getDamping());
        m_orientation = other.m_orientation;
        m_rotation = other.m_rotation;
        m_angularAcceleration = other.m_angularAcceleration;
    }
    return *this;
}

// Getters
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

// Setters
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
    m_transformationMatrix.setOrientationAndPosition(m_orientation, getPosition());
}

// integrate the rigid body by modifying position, orientation and velocities
void RigidBody::integratePosition(float deltaT)
{
    //We update the position, the same way we did with the particles
    setPosition(getPosition() + getVelocity() * deltaT + getAcceleration() * 0.5 * pow(deltaT, 2));

    //We update the orientation thanks to the quaternion class's method
    m_orientation.updateByAngularVelocity(m_rotation, deltaT);

    //We update the transformation matrix for the graphical engine
    calculateDerivedData();

    //We reset the accelerations
    setAcceleration(Vector3D());
    setAngularAcceleration(Vector3D());
}

void RigidBody::integrateVelocity(float deltaT)
{
    // Update velocity
    setVelocity(getVelocity() * pow(getDamping(), deltaT));
    setVelocity(getVelocity() + getAcceleration() * deltaT);

    // Update angular velocity
    m_rotation *= pow(getDamping(), deltaT);
    m_rotation += m_angularAcceleration * deltaT;

    // Update deltaT to last deltaT
    setDeltaT(deltaT);
}

std::ostream& operator<<(std::ostream& out, RigidBody const& rb)
{
    out << "Position : " << rb.getPosition() << ", " << std::endl
        << "Velocity : " << rb.getVelocity() << ", " << std::endl
        << "Orientation : " << rb.m_orientation << ", " << std::endl
        << "Rotation : " << rb.m_rotation;
    return out;
}
} // namespace engine
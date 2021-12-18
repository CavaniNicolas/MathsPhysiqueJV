
#include "PhysicsEngine/RigidBody.hpp"

namespace engine
{
RigidBody::RigidBody(Vector3D position,
                     Vector3D velocity,
                     Quaternion rotation,
                     Vector3D angularVelocity,
                     float dx,
                     float dy,
                     float dz,
                     float mass,
                     float g,
                     float damping,
                     float angularDamping):
  PhysicsObject(position, velocity, mass, g, damping),
  m_orientation(rotation),
  m_rotation(angularVelocity),
  m_angularDamping(angularDamping),
  m_dx(dx),
  m_dy(dy),
  m_dz(dz)
{
    calculateInertiaMatrix();
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
        m_angularDamping = other.m_angularDamping;
        m_dx = other.m_dx;
        m_dy = other.m_dy;
        m_dz = other.m_dz;

        calculateInertiaMatrix();
        m_transformationMatrix = Matrix34();
        calculateDerivedData();
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
        m_angularDamping = other.m_angularDamping;
        m_dx = other.m_dx;
        m_dy = other.m_dy;
        m_dz = other.m_dz;

        calculateInertiaMatrix();
        m_transformationMatrix = Matrix34();
        calculateDerivedData();
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
Matrix34 RigidBody::getTransformationMatrix() const
{
    return m_transformationMatrix;
}

float RigidBody::getDx() const
{
    return m_dx;
}

float RigidBody::getDy() const
{
    return m_dy;
}

float RigidBody::getDz() const
{
    return m_dz;
}

Matrix33 RigidBody::getInertiaInverseMatrix() const
{
    return m_worldInertiaInverseMatrix;
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
    // We normalize the orientation quaternion
    m_orientation.normalized();

    // We update the transformation matrix for the graphical engine
    m_transformationMatrix.setOrientationAndPosition(m_orientation, getPosition());

    // We update the world inertia matrix
    m_worldInertiaInverseMatrix = m_transformationMatrix.getMatrix33() * m_localInertiaInverseMatrix *
                                  m_transformationMatrix.getMatrix33().inverse();
}

// integrate the rigid body by modifying position, orientation and velocities
void RigidBody::integratePosition(float deltaT)
{
    // We update the position, the same way we did with the particles
    m_position += m_velocity * deltaT;

    // We update the orientation thanks to the quaternion class's method
    m_orientation.updateByAngularVelocity(m_rotation, deltaT);

    // We update the transformation matrix for the graphical engine
    calculateDerivedData();

    // Update deltaT to last deltaT
    m_deltaT = deltaT;

    // We reset the accelerations
    m_acceleration = Vector3D();
    m_angularAcceleration = Vector3D();
}

void RigidBody::integrateVelocity(float deltaT)
{
    // Calculate regular acceleration
    m_acceleration = m_forceAccum * getInverseMass();
    // Calculate angular acceleration
    m_angularAcceleration = m_worldInertiaInverseMatrix * m_torqueAccum;

    Vector3D newVelocity = m_velocity * pow(m_linearDamping, deltaT) + m_acceleration * deltaT;
    // Update velocity
    m_velocity = newVelocity;

    // Update angular velocity
    m_rotation = m_rotation * pow(m_angularDamping, deltaT) + m_angularAcceleration * deltaT;

    // reset forces accum
    clearAccumulator();
}

void RigidBody::addForce(const Vector3D& force)
{
    m_forceAccum += force;
}

void RigidBody::addForceAtPoint(const Vector3D& force, const Vector3D& worldPoint)
{
    Vector3D torque = (worldPoint).crossProduct(force);
    m_torqueAccum += torque;
    m_forceAccum += force;
}

void RigidBody::addForceAtBodyPoint(const Vector3D& force, const Vector3D& localPoint)
{
    Vector3D torque = (m_transformationMatrix * localPoint).crossProduct(force);
    m_torqueAccum += torque;
    m_forceAccum += force;
}

void RigidBody::clearAccumulator()
{
    m_torqueAccum = Vector3D();
    m_forceAccum = Vector3D();
}

Vector3D RigidBody::localToWorldCoordinates(Vector3D& coordinates)
{
    return m_transformationMatrix * coordinates;
}

void RigidBody::calculateInertiaMatrix()
{
    std::array<float, 3> line1 = {(1.0f / 12.0f) * getMass() * (m_dy * m_dy + m_dz * m_dz), 0, 0};
    std::array<float, 3> line2 = {0, (1.0f / 12.0f) * getMass() * (m_dx * m_dx + m_dz * m_dz), 0};
    std::array<float, 3> line3 = {0, 0, (1.0f / 12.0f) * getMass() * (m_dy * m_dy + m_dx * m_dx)};

    m_localInertiaInverseMatrix = Matrix33(line1, line2, line3).inverse();
}

Vector3D RigidBody::getOrientationEuler() const
{
    return m_orientation.getEuler();
}

float RigidBody::getGreatestRadius() const
{
    return std::sqrt(m_dx * m_dx + m_dy * m_dy + m_dz * m_dz) / 2;
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

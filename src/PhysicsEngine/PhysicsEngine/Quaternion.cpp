
#include "PhysicsEngine/Quaternion.hpp"

namespace engine
{

Quaternion::Quaternion(): m_w(0), m_x(0), m_y(0), m_z(1) {}

Quaternion::Quaternion(float w, float x, float y, float z): m_w(w), m_x(x), m_y(y), m_z(z) {}

void Quaternion::normalized()
{
    float norm = getNorm();
    m_w = m_w / norm;
    m_x = m_x / norm;
    m_y = m_y / norm;
    m_z = m_z / norm;
}

// corresponds to the rotation of other then of *this
Quaternion Quaternion::operator*(const Quaternion& other)
{
    float w = m_w * other.m_w - m_x * other.m_x - m_y * other.m_y - m_z * other.m_z;
    float i = m_w * other.m_x + m_x * other.m_w + m_y * other.m_z - m_z * other.m_y;
    float j = m_w * other.m_y + m_y * other.m_w + m_z * other.m_x - m_x * other.m_z;
    float k = m_w * other.m_z + m_z * other.m_w + m_x * other.m_y - m_y * other.m_x;
    return Quaternion(w, i, j, k);
}

// Rotate the quaternion by a vector - multiply this by q = (0, dx, dy, dz)
void Quaternion::rotateByVector(const Vector3D& vector)
{
    // quat is only used for the calculations
    Quaternion quat(0, vector.getX(), vector.getY(), vector.getZ());
    quat = *this * quat;

    // maybe think of implementing operator=()
    m_w = quat.m_w;
    m_x = quat.m_x;
    m_y = quat.m_y;
    m_z = quat.m_z;

    normalized();
}

void Quaternion::updateByAngularVelocity(const Vector3D& rotation, float deltaT)
{
    // this = this + (deltaT/2) * angularVelocity * this
    // quat is only used for the calculations
    Quaternion quat(0, rotation.getX(), rotation.getY(), rotation.getZ());
    quat = quat * *this;
    quat.scalarMultiplication(deltaT / 2);
    *this += quat;

    normalized();
}

float Quaternion::getNorm() const
{
    return sqrt(m_w * m_w + m_x * m_x + m_y * m_y + m_z * m_z);
}

Quaternion& Quaternion::operator+=(const Quaternion& quat)
{
    m_w += quat.m_w;
    m_x += quat.m_x;
    m_y += quat.m_y;
    m_z += quat.m_z;
    return *this;
}

Quaternion& Quaternion::scalarMultiplication(const float scalar)
{
    m_w *= scalar;
    m_x *= scalar;
    m_y *= scalar;
    m_z *= scalar;
    return *this;
}

} // namespace engine

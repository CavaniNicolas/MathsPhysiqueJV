
#include "PhysicsEngine/Quaternion.hpp"

namespace engine
{

Quaternion::Quaternion(): m_w(1), m_x(0), m_y(0), m_z(0) {}

Quaternion::Quaternion(float w, float x, float y, float z): m_w(w), m_x(x), m_y(y), m_z(z) {}

void Quaternion::normalized()
{
    *this /= getNorm();
}

// corresponds to the rotation of other then of *this
Quaternion Quaternion::operator*(const Quaternion& other)
{
    float w = m_w * other.m_w - m_x * other.m_x - m_y * other.m_y - m_z * other.m_z;
    float x = m_w * other.m_x + m_x * other.m_w + m_y * other.m_z - m_z * other.m_y;
    float y = m_w * other.m_y + m_y * other.m_w + m_z * other.m_x - m_x * other.m_z;
    float z = m_w * other.m_z + m_z * other.m_w + m_x * other.m_y - m_y * other.m_x;
    return Quaternion(w, x, y, z);
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
}

void Quaternion::updateByAngularVelocity(const Vector3D& rotation, float deltaT)
{
    // this = this + (deltaT/2) * angularVelocity * this
    // quat is only used for the calculations
    Quaternion quat(0, rotation.getX(), rotation.getY(), rotation.getZ());
    quat = quat * *this;
    quat *= deltaT / 2.0;
    *this += quat;
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

Quaternion& Quaternion::operator*=(const float scalar)
{
    m_w *= scalar;
    m_x *= scalar;
    m_y *= scalar;
    m_z *= scalar;
    return *this;
}

Quaternion& Quaternion::operator/=(const float scalar)
{
    m_w /= scalar;
    m_x /= scalar;
    m_y /= scalar;
    m_z /= scalar;
    return *this;
}

std::ostream& operator<<(std::ostream& out, Quaternion const& quat)
{
    out << "w:" << quat.m_w << ", x:" << quat.m_x << ", y:" << quat.m_y << ", z:" << quat.m_z;
    return out;
}

} // namespace engine

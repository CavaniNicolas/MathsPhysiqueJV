
#include "PhysicsEngine/Quaternion.hpp"

namespace engine
{

Quaternion::Quaternion(float w, float i, float j, float k): m_w(w), m_i(i), m_j(j), m_k(k) {}

void Quaternion::normalized() {}

// corresponds to the rotation of other then of *this
Quaternion Quaternion::operator*(const Quaternion& other)
{
    float w = m_w * other.m_w - m_i * other.m_i - m_j * other.m_j - m_k * other.m_k;
    float i = m_w * other.m_i + m_i * other.m_w + m_j * other.m_k - m_k * other.m_j;
    float j = m_w * other.m_j + m_j * other.m_w + m_k * other.m_i - m_i * other.m_k;
    float k = m_w * other.m_k + m_k * other.m_w + m_i * other.m_j - m_j * other.m_i;
    return Quaternion(w, i, j, k);
}

void Quaternion::rotateByVector(const Vector3D& vector) {}

void Quaternion::updateByAngularVelocity(const Vector3D& rotation, float deltaT) {}

} // namespace engine

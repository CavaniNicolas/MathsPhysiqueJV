#pragma once

#include "PhysicsEngine/Vector3D.hpp"

namespace engine
{

class Quaternion
{
  private:
    // w, i, j, k
    float m_w;
    float m_i;
    float m_j;
    float m_k;

  public:
    Quaternion(float w, float i, float j, float k);

    // normalize by multiplying the quaternion by the inverse of its magnitude
    void normalized();

    // Quaternion multiplication
    Quaternion operator*(const Quaternion& other);

    // Rotate the quaternion by a vector - multiply this by q = (0, dx, dy, dz)
    void rotateByVector(const Vector3D& vector);

    // Apply the quaternion update by the angular velocity
    void updateByAngularVelocity(const Vector3D& rotation, float deltaT);
};

} // namespace engine

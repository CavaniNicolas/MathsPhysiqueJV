#pragma once

#include "PhysicsEngine/Vector3D.hpp"

namespace engine
{

class Quaternion
{
  private:
    // w, x, y, z
    float m_w;
    float m_x;
    float m_y;
    float m_z;

  public:
    Quaternion();
    Quaternion(float w, float x, float y, float z);

    // normalize by multiplying the quaternion by the inverse of its magnitude
    void normalized();

    // Quaternion multiplication
    Quaternion operator*(const Quaternion& other);

    // Rotate the quaternion by a vector - multiply this by q = (0, dx, dy, dz)
    void rotateByVector(const Vector3D& vector);

    // Apply the quaternion update by the angular velocity
    void updateByAngularVelocity(const Vector3D& rotation, float deltaT);

    float getNorm() const;

    inline float getW() const
    {
        return m_w;
    }

    inline float getX() const
    {
        return m_x;
    }

    inline float getY() const
    {
        return m_y;
    }

    inline float getZ() const
    {
        return m_z;
    }

    Vector3D getEuler() const;

    friend std::ostream& operator<<(std::ostream& out, Quaternion const& rb);

  private:
    Quaternion& operator+=(const Quaternion& quat);
    Quaternion& operator*=(const float scalar);
    Quaternion& operator/=(const float scalar);
};

} // namespace engine

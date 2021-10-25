#pragma once

#include <array>
#include "PhysicsEngine/Vector3D.hpp"

class Matrix34
{
  private:
    // values of the matrix 3x3
    std::array<std::array<float, 3>, 4> m_values;

  public:
    // combination of affine transformation
    Matrix34 operator*(const Matrix34& other) const;

    // Transform a vector
    Vector3D operator*(const Vector3D& vector) const;

    // Get the inverse matrix
    Matrix34 inverse();

    // Set the matrix base on a quaternion
    void setOrientationAndPosition(const Quaternion& q, const Vector3D& p);

    // Transform a position
    Vector3D transformPosition(const Vector3D& vector);

    //Transform a direction by ignoring the translation
    Vector3D transformDirection(const Vector3D& vector);
};
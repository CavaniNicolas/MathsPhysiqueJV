#pragma once

#include <array>
#include "PhysicsEngine/Vector3D.hpp"

namespace engine
{
class Matrix33
{
  private:
    // values of the matrix 3x3
    std::array<std::array<float, 3>, 3> m_values;

  public:
    // combination of linear transformation
    Matrix33 operator*(const Matrix33& other) const;

    // Transform a vector
    Vector3D operator*(const Vector3D& vector) const;

    // Get the inverse matrix
    Matrix33 inverse();

    // Get the transpose matrix
    Matrix33 transpose();

    // Set the matrix base on a quaternion
    void setOrientation(const Quaternion& q);
};
} // namespace engine
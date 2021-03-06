#pragma once

#include <array>
#include "PhysicsEngine/Matrix33.hpp"
#include "PhysicsEngine/Vector3D.hpp"
#include "PhysicsEngine/Quaternion.hpp"

namespace engine
{
class Matrix34
{
  private:
    // values of the matrix 4x3
    std::array<std::array<float, 4>, 3> m_values;

  public:
    Matrix34(std::array<float, 4> line1, std::array<float, 4> line2, std::array<float, 4> line3);
    Matrix34();

    // combination of affine transformation
    Matrix34 operator*(const Matrix34& other) const;

    // Transform a vector
    Vector3D operator*(const Vector3D& vector) const;

    // Get the inverse matrix
    Matrix34 inverse();

    // Set the matrix base on a quaternion
    void setOrientationAndPosition(const Quaternion& q, const Vector3D& p);

    // Transform a position
    Vector3D transformPosition(const Vector3D& vector) const;

    // Transform a direction by ignoring the translation
    Vector3D transformDirection(const Vector3D& vector) const;

    // return m_values
    std::array<std::array<float, 4>, 3> getValuesArray() const;

    Matrix33 getMatrix33() const;

    void printMatrix() const;
};
} // namespace engine

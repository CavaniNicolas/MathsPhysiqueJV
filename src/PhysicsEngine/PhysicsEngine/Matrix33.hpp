#pragma once

#include <array>
#include "PhysicsEngine/Vector3D.hpp"
#include "Quaternion.hpp"

namespace engine
{
class Matrix33
{
  private:
    // values of the matrix 3x3
    std::array<std::array<float, 3>, 3> m_values;

  public:
    Matrix33(std::array<float, 3> line1, std::array<float, 3> line2, std::array<float, 3> line3);
    Matrix33();

    std::array<std::array<float, 3>, 3> getValues();

    // combination of linear transformation
    Matrix33 operator*(const Matrix33& other) const;

    // Transform a vector
    Vector3D operator*(const Vector3D& vector) const;

    // Multiply by a scalar
    Matrix33 operator*(const float scalar) const;

    // Get the inverse matrix
    Matrix33 inverse();

    // Get the transpose matrix
    Matrix33 transpose();

    // Set the matrix base on a quaternion
    void setOrientation(const Quaternion& q);

    // Marche pas
    // friend std::ostream& operator<<(std::ostream& out, Matrix33 const& matrix);

    void printMatrix() const;

    float calculateDeterminant33() const;
};

} // namespace engine

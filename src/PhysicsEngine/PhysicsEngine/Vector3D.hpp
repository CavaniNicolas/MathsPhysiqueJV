#pragma once

#include <iostream>
#include <stdio.h>

namespace engine
{

class Vector3D
{
  private:
    float m_x;
    float m_y;
    float m_z;

  public:
    // Constructors
    Vector3D(float x = 0.0, float y = 0.0, float z = 0.0);
    Vector3D(const Vector3D& other);

    // Assignation
    Vector3D& operator=(const Vector3D& other);

    // Setters
    void setCoord(float x, float y, float z);
    void setCoord(const Vector3D& vector);
    void setX(float x);
    void setY(float y);
    void setZ(float z);

    // Getters
    float getX() const;
    float getY() const;
    float getZ() const;

    // Operations
    //	with a Vector3D
    Vector3D operator+(const Vector3D& vector) const;
    Vector3D& operator+=(const Vector3D& vector);
    Vector3D operator-(const Vector3D& vector) const;
    Vector3D& operator-=(const Vector3D& vector);
    float scalarProduct(const Vector3D& vector) const;
    Vector3D crossProduct(const Vector3D& vector) const;
    //	with a scalar
    Vector3D operator*(const float scalar) const;
    Vector3D& operator*=(const float scalar);
    Vector3D operator/(const float scalar) const;
    Vector3D& operator/=(const float scalar);
    Vector3D operator^(const float scalar) const;
    Vector3D& operator^=(const float scalar);

    friend bool operator==(const Vector3D v1, const Vector3D v2);

    // Other methods
    float getNorm() const;
    float getSquareNorm() const;
    Vector3D normalize() const;
    static Vector3D getVectorInput();
    static float distance(Vector3D vect1, Vector3D vect2);
    static float squareDistance(Vector3D vect1, Vector3D vect2);

    friend std::ostream& operator<<(std::ostream& out, Vector3D const& vector);
};

} // namespace engine

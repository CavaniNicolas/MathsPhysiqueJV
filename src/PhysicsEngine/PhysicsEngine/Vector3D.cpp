
#include <cmath>
#include <iostream>
#include <regex>

#include "PhysicsEngine/Vector3D.hpp"

// Constructors
Vector3D::Vector3D(float x, float y, float z)
{
    m_x = x;
    m_y = y;
    m_z = z;
}

Vector3D::Vector3D(const Vector3D& other): Vector3D(other.m_x, other.m_y, other.m_z) {}

// Assignation
Vector3D& Vector3D::operator=(const Vector3D& other)
{
    m_x = other.m_x;
    m_y = other.m_y;
    m_z = other.m_z;

    return *this;
}

// Setters
void Vector3D::setCoord(float x, float y, float z)
{
    m_x = x;
    m_y = y;
    m_z = z;
}

void Vector3D::setCoord(const Vector3D& vector)
{
    setCoord(vector.m_x, vector.m_y, vector.m_z);
}

void Vector3D::setX(float x)
{
    m_x = x;
}

void Vector3D::setY(float y)
{
    m_y = y;
}

void Vector3D::setZ(float z)
{
    m_z = z;
}

// Getters
float Vector3D::getX() const
{
    return m_x;
}

float Vector3D::getY() const
{
    return m_y;
}

float Vector3D::getZ() const
{
    return m_z;
}

// Operations
//	with a Vector3D
Vector3D Vector3D::operator+(const Vector3D& vector) const
{
    return Vector3D(m_x + vector.m_x, m_y + vector.m_y, m_z + vector.m_z);
}

Vector3D& Vector3D::operator+=(const Vector3D& vector)
{
    *this = *this + vector;
    return *this;
}

Vector3D Vector3D::operator-(const Vector3D& vector) const
{
    return Vector3D(m_x - vector.m_x, m_y - vector.m_y, m_z - vector.m_z);
}

Vector3D& Vector3D::operator-=(const Vector3D& vector)
{
    *this = *this - vector;
    return *this;
}

float Vector3D::scalarProduct(const Vector3D& vector) const
{
    return (m_x * vector.m_x + m_y * vector.m_y + m_z * vector.m_z);
}

Vector3D Vector3D::crossProduct(const Vector3D& vector) const
{
    return Vector3D(
      m_y * vector.m_z - m_z * vector.m_y, m_z * vector.m_x - m_x * vector.m_z, m_x * vector.m_y - m_y * vector.m_x);
}

//	with a scalar
Vector3D Vector3D::operator*(const float scalar) const
{
    return Vector3D(m_x * scalar, m_y * scalar, m_z * scalar);
}

Vector3D& Vector3D::operator*=(const float scalar)
{
    *this = *this * scalar;
    return *this;
}

Vector3D Vector3D::operator/(const float scalar) const
{
    return Vector3D(m_x / scalar, m_y / scalar, m_z / scalar);
}

Vector3D& Vector3D::operator/=(const float scalar)
{
    *this = *this / scalar;
    return *this;
}

Vector3D Vector3D::operator^(const float scalar) const
{
    return Vector3D(pow(m_x, scalar), pow(m_y, scalar), pow(m_z, scalar));
}

Vector3D& Vector3D::operator^=(const float scalar)
{
    *this = *this ^ scalar;
    return *this;
}

// Other methods
float Vector3D::getNorm() const
{
    return sqrt(pow(m_x, 2) + pow(m_y, 2) + pow(m_z, 2));
}

Vector3D Vector3D::normalize() const
{
    float norm = getNorm();
    if(norm == 0)
    {
        return Vector3D();
    }
    else
    {
        return *this / getNorm();
    }
}

Vector3D Vector3D::getVectorInput()
{
    std::string strVector;
    while(1)
    {
        std::cin >> strVector;
        if(std::regex_match(strVector, std::regex("\\((-?[0-9]+(.[0-9])?),(-?[0-9]+(.[0-9])?),(-?[0-9]+(.[0-9])?)\\)")))
        {
            std::smatch matches;
            if(regex_search(strVector,
                            matches,
                            std::regex("\\((-?[0-9]+(.[0-9])?),(-?[0-9]+(.[0-9])?),(-?[0-9]+(.[0-9])?)\\)")) == true)
            {
                float x = std::stof(matches[1]);
                float y = std::stof(matches[3]);
                float z = std::stof(matches[5]);
                Vector3D vector = Vector3D(x, y, z);
                return vector;
            }
        }
        else
        {
            std::cout << "Please respect the format (x,y,z). Input your vector: ";
            continue;
        }
    }
}

std::ostream& operator<<(std::ostream& out, Vector3D const& vector)
{
    out << "(" << vector.m_x << ", " << vector.m_y << ", " << vector.m_z << ")";
    return out;
}

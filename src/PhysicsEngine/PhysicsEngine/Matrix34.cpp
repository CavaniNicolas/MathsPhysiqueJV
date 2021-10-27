#include "Matrix34.hpp"
#include "Matrix33.hpp"

using namespace engine;

Matrix34::Matrix34(std::array<float, 4> line1, std::array<float, 4> line2, std::array<float, 4> line3)
{
    m_values[0] = line1;
    m_values[1] = line2;
    m_values[2] = line3;
}

Matrix34::Matrix34()
{
    m_values[0] = {1, 0, 0, 0};
    m_values[1] = {0, 1, 0, 0};
    m_values[2] = {0, 0, 1, 0};
}

// combination of affine transformation
Matrix34 Matrix34::operator*(const Matrix34& other) const
{
    Matrix34 result = Matrix34();
    for(int i = 0; i < m_values.size(); i++)
    // i = line number
    {
        for(int j = 0; j < m_values[0].size(); j++)
        {
            float res = 0;
            for(int k = 0; k < m_values[j].size(); k++)
            {
                res += m_values[i][k] * other.m_values[k][j];
            }
            result.m_values[i][j] = res;
        }
    }
    return result;
}

// Transform a vector
Vector3D Matrix34::operator*(const Vector3D& vector) const
{
    float x =
      m_values[0][0] * vector.getX() + m_values[0][1] * vector.getY() + m_values[0][2] * vector.getZ() + m_values[0][3];
    float y =
      m_values[1][0] * vector.getX() + m_values[1][1] * vector.getY() + m_values[1][2] * vector.getZ() + m_values[0][3];
    float z =
      m_values[2][0] * vector.getX() + m_values[2][1] * vector.getY() + m_values[2][2] * vector.getZ() + m_values[0][3];

    return Vector3D(x, y, z);
}

// Get the inverse matrix
Matrix34 Matrix34::inverse() {

    Matrix33 subMatrix = Matrix33({m_values[0][0], m_values[0][1], m_values[0][2]},
                                  {m_values[1][0], m_values[1][1], m_values[1][2]},
                                  {m_values[2][0], m_values[2][1], m_values[2][2]});

    subMatrix = subMatrix.inverse();

    Matrix34 inverse = Matrix34();
    Vector3D v = Vector3D(m_values[0][3], m_values[1][3], m_values[2][3]);
    v = subMatrix * (v * -1);

    std::array<std::array<float,3>,3> values = subMatrix.getValues();

    inverse.m_values[0] = {values[0][0], values[0][1], values[0][2], v.getX()};
    inverse.m_values[1] = {values[1][0], values[1][1], values[1][2], v.getY()};
    inverse.m_values[2] = {values[2][0], values[2][1], values[2][2], v.getZ()};

    return inverse;
}

// Set the matrix base on a quaternion
void Matrix34::setOrientationAndPosition(const Quaternion& q, const Vector3D& p) {
    /*float w = q.getW();
    float x = q.getI();
    float y = q.getJ();
    float z = q.getK();*/

    /*m_values[0][0] = 1 - (2 * pow(y, 2) + 2 * pow(z, 2));
    m_values[0][1] = 2 * x * y + 2 * z * w;
    m_values[0][2] = 2 * x * z + 2 * y * w;
    m_values[1][0] = 2 * x * y - 2 * z * w;
    m_values[1][1] = 1 - (2 * pow(x, 2) + 2 * pow(z, 2));
    m_values[1][2] = 2 * y * z + 2 * x * w;
    m_values[2][0] = 2 * x * z + 2 * y * w;
    m_values[2][1] = 2 * y * z - 2 * x * w;
    m_values[2][2] = 1 - (2 * pow(x, 2) + 2 * pow(y, 2));*/

    /*
    m_values[0][3] = p.getX();
    m_values[1][3] = p.getY();
    m_values[2][3] = p.getz();
    */
}

// Transform a position
Vector3D Matrix34::transformPosition(const Vector3D& vector)
{
    return *this * vector;
}

// Transform a direction by ignoring the translation
Vector3D Matrix34::transformDirection(const Vector3D& vector) {
    Matrix33 m = Matrix33({m_values[0][0], m_values[0][1], m_values[0][2]},
                          {m_values[1][0], m_values[1][1], m_values[1][2]},
                          {m_values[2][0], m_values[2][1], m_values[2][2]});

    return m * vector;
}
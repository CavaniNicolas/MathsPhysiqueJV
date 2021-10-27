#include "PhysicsEngine/Matrix33.hpp"
#include <format>
#include <iostream>

using namespace engine;

Matrix33::Matrix33(std::array<float, 3> line1, std::array<float, 3> line2, std::array<float, 3> line3)
{
    m_values[0] = line1;
    m_values[1] = line2;
    m_values[2] = line3;
}

Matrix33::Matrix33() {
    m_values[0] = { 0, 0, 0 };
    m_values[1] = { 0, 0, 0 };
    m_values[2] = { 0, 0, 0 };
}

// combination of linear transformation
Matrix33 Matrix33::operator*(const Matrix33& other) const
{
    Matrix33 result = Matrix33();
    for(int i = 0; i < m_values.size(); i++)
        // i = line number
    {
        for (int j = 0; j < m_values[0].size(); j++)
        {
            float res = 0;
            for(int k = 0; k < m_values[j].size(); k++) {
                res += m_values[i][k] * other.m_values[k][j];
            }
            result.m_values[i][j] = res;
        }
    }
    return result;
}

// Transform a vector
Vector3D Matrix33::operator*(const Vector3D& vector) const
{
    Vector3D result;

    float x = m_values[0][0] * vector.getX() + m_values[0][1] * vector.getY() + m_values[0][2] * vector.getZ();
    float y = m_values[1][0] * vector.getX() + m_values[1][1] * vector.getY() + m_values[1][2] * vector.getZ();
    float z = m_values[2][0] * vector.getX() + m_values[2][1] * vector.getY() + m_values[2][2] * vector.getZ();

    return Vector3D(x,y,z);
}

Matrix33 Matrix33::operator*(const float scalar) const {
    Matrix33 result;
    for (int i = 0; i < m_values.size(); i++) {
        for (int j = 0; j < m_values[i].size(); j++) {
            result.m_values[i][j] = m_values[i][j] * scalar; 
        }
    }
    return result;
}



float Matrix33::calculateDeterminant33() const {
    float determinant = 0;
    // we choose a line, the first one
    int line = 0;
    int column = 0;
    for (column; column < m_values[line].size(); column++) {
        float coef = m_values[line][column];
        if ((line + column) % 2 == 0) {
            //L+C even  -> coef = 1
            coef *= 1;
        }
        else
        {
            //L+C odd -> coef = -1
            coef *= -1;
        }
        // We calculate the sub 2x2 matrix that we will use to calculate the determinant
        std::array<float, 2> line1;
        std::array<float, 2> line2;
        switch(column)
        {
            case 0: 
                line1 = {m_values[1][1], m_values[1][2]}; 
                line2 = {m_values[2][1], m_values[2][2]};
                break;
            case 1:
                line1 = {m_values[1][0], m_values[1][2]};
                line2 = {m_values[2][0], m_values[2][2]};
                break;
            case 2:
                line1 = {m_values[1][0], m_values[1][1]};
                line2 = {m_values[2][0], m_values[2][1]};
                break;

        }
        // determinant of the sub matrix
        float determinant22 = line1[0] * line2[1] - line1[1] * line2[0];
        determinant += coef * determinant22;

    }
    return determinant;
}

// Get the inverse matrix
Matrix33 Matrix33::inverse()
{
    //first we check if the matrix can be inversed
    // <=> we check if its determinant is != 0
    float determinant = calculateDeterminant33();
    if (determinant == 0) {
        std::cerr << "ERROR: Cannot inverse a matrix with a null determinant !" << std::endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        Matrix33 inverse = Matrix33();
        float a = m_values[0][0];
        float b = m_values[0][1];
        float c = m_values[0][2];
        float d = m_values[1][0];
        float e = m_values[1][1];
        float f = m_values[1][2];
        float g = m_values[2][0];
        float h = m_values[2][1];
        float i = m_values[2][2];

        inverse.m_values[0] = {(e * i - f * h), (c * h - b * i), (b * f - c * e)};
        inverse.m_values[1] = {(f * g - d * i), (a * i - c * g), (c * d - a * f)};
        inverse.m_values[2] = {(d * h - e * g), (b * g - a * h), (a * e - b * d)};

        inverse = inverse * (1 / determinant);
        return inverse;
    }

    
}

// Get the transpose matrix
Matrix33 Matrix33::transpose() {
    Matrix33 transpose = Matrix33();
    float a = m_values[0][0];
    float b = m_values[0][1];
    float c = m_values[0][2];
    float d = m_values[1][0];
    float e = m_values[1][1];
    float f = m_values[1][2];
    float g = m_values[2][0];
    float h = m_values[2][1];
    float i = m_values[2][2];

    transpose.m_values[0] = {a, d, g};
    transpose.m_values[1] = {b, e, h};
    transpose.m_values[2] = {c, f, i};
    return transpose;
}

// Set the matrix base on a quaternion
void Matrix33::setOrientation(const Quaternion& q)
{
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

}

std::array<std::array<float, 3>, 3> Matrix33::getValues() {
    return m_values;
}

void Matrix33::printMatrix() const {
    
    std::cout << "(";
    for (int i = 0; i < m_values.size(); i++) {
        for (int j = 0; j < m_values[i].size(); j++) {
            std::cout << m_values[i][j] << ",";
        }
        std::cout << std::endl;
    }
    std::cout << ")" << std::endl;
   
}
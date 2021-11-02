#include "PhysicsEngine/Matrix33.hpp"

using namespace engine;

int main()
{
    // Matrix33 m1 = Matrix33({1, 2, 3}, {2, 3, 1}, {3, 1, 2});
    // Matrix33 m2 = Matrix33({1, 2, 3}, {2, 3, 1}, {3, 1, 2});
    ///*Matrix33 m3 = m1 * m2;
    // m3.printMatrix();*/

    // Vector3D v = Vector3D(1, 2, 1);

    Matrix33 m1 = Matrix33({1, 2, 3}, {3, 4, 5}, {5, 6, 7});

    m1.inverse().printMatrix();
}
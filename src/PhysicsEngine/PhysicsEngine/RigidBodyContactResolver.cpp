#include "PhysicsEngine/RigidBodyContactResolver.hpp"

namespace engine
{
bool RigidBodyContactResolver::resolveContacts(RigidBodyCollisionData& collisionData) {
    if (collisionData.popContacts().size() > 0) {
        return true;
    }
    return false;
}
//std::vector<Vector3D> RigidBodyContactResolver::getOrthogonalBasis(const Vector3D& normal)
//{
//    std::vector<Vector3D> basis;
//    Vector3D a = normal.normalize();
//    basis.push_back(a);
//    Vector3D c = a.crossProduct(Vector3D(1, 0, 0).normalize());
//    basis.push_back(c.crossProduct(a));
//    basis.push_back(c);
//    return basis;
//}
//
//Vector3D RigidBodyContactResolver::getImpulsion(const RigidBodyContact& rigidBodyContact)
//{   
//    //changement de vélocité - composant linéaire
//    float linearVelocityChange;
//    if (rigidBodyContact.getOtherRigidBody() != nullptr) {
//        linearVelocityChange =
//          rigidBodyContact.getRigidBody()->getInverseMass() + rigidBodyContact.getOtherRigidBody()->getInverseMass();
//    }
//    else
//    {
//        linearVelocityChange = rigidBodyContact.getRigidBody()->getInverseMass();
//    }
//
//    //changement de velocité - composant angulaire
//    Vector3D angularVelocityChange;
//    Vector3D qrel = rigidBodyContact.getContactPoint() - rigidBodyContact.getRigidBody()->getPosition();
//    Vector3D u = qrel.crossProduct(rigidBodyContact.getContactNormal().normalize());
//    Vector3D teta = rigidBodyContact.getRigidBody()->getInertiaInverseMatrix() * u;
//
//    angularVelocityChange = teta.crossProduct(qrel);
//
//    if (rigidBodyContact.getOtherRigidBody() != nullptr) {
//        Vector3D qrel2 = rigidBodyContact.getContactPoint() - rigidBodyContact.getOtherRigidBody()->getPosition();
//        Vector3D u2 = qrel2.crossProduct(rigidBodyContact.getContactNormal().normalize());
//        Vector3D teta2 = rigidBodyContact.getOtherRigidBody()->getInertiaInverseMatrix() * u2;
//        angularVelocityChange += teta2.crossProduct(qrel2);
//    }
//     
//    //changement de vélocité
//    Vector3D velocityChange = angularVelocityChange + linearVelocityChange;
//   
//}
} // namespace engine
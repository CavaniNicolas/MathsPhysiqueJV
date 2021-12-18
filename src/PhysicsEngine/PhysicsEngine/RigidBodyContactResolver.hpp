#pragma once

#include "PhysicsEngine/RigidBodyCollisionData.hpp"

namespace engine
{
class RigidBodyContactResolver
{
  public:
    bool resolveContacts(RigidBodyCollisionData& collisionData);    
    /*std::vector<Vector3D> getOrthogonalBasis(const Vector3D& normal);
    Vector3D getImpulsion(const RigidBodyContact& rigidBodyContact);*/
};
}
#pragma once

#include "PhysicsEngine/RigidBodyCollisionData.hpp"

namespace engine
{
//class RigidBody;
//class RigidBodyCollisionData;

class Primitive
{
  private:
    std::shared_ptr<RigidBody> m_body;
    Matrix34 m_offset;

  public:
    Primitive(std::shared_ptr<RigidBody> body, Matrix34 offset);

    std::shared_ptr<RigidBody> getRigidBody() const;
    Matrix34 getOffset() const;

    void setRigidBody(std::shared_ptr<RigidBody> body);
    void setOffset(Matrix34 offset);

    Vector3D getPosition() const;

    virtual float getYMax() const = 0;

    virtual void generateContactWith(const std::shared_ptr<Primitive>& other, RigidBodyCollisionData& collisionData) = 0;
};
} // namespace engine
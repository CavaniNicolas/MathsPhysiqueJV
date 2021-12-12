#pragma once

#include "PhysicsEngine/RigidBody.hpp"

namespace engine
{
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
};
} // namespace engine
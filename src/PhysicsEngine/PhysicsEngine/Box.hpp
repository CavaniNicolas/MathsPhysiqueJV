#pragma once

#include "PhysicsEngine/Primitive.hpp"

namespace engine
{
class Box : public Primitive
{
  private:
    Vector3D m_halfSizes;

  public:
    Box(std::shared_ptr<RigidBody> body, Matrix34 offset, Vector3D halfSizes);

    Vector3D getHalfSizes() const;

    void setHalfSizes(Vector3D halfSizes);

    float getGreatestHalfSize() const;

    virtual bool collidesWith(const std::shared_ptr<Primitive>& other);
};
} // namespace engine
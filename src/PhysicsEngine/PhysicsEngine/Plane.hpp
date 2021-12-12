#pragma once

#include "PhysicsEngine/Primitive.hpp"

namespace engine
{
class Plane : public Primitive
{
  private:
    Vector3D m_normal;
    float m_planeOffset;

    public:
    Plane(std::shared_ptr<RigidBody> body, Matrix34 offset, Vector3D normal, float planeOffset);

    Vector3D getNormal() const;
    float getPlaneOffset() const;

    void setNormal(Vector3D normal);
    void setPlaneOffset(float planeOffset);
};
}
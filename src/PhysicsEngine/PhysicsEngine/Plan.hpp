#pragma once

#include "PhysicsEngine/Primitive.hpp"

namespace engine
{
class Plan : public Primitive
{
  private:
    Vector3D m_normal;
    float m_planOffset;

    public:
    Plan(Matrix34 offset, Vector3D normal, float planOffset);

    Vector3D getNormal() const;
    float getPlanOffset() const;

    void setNormal(Vector3D normal);
    void setPlanOffset(float planOffset);

    virtual bool collidesWith(const std::shared_ptr<Primitive>& other);
};
}
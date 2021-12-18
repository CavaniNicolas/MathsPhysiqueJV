#pragma once

#include "PhysicsEngine/Primitive.hpp"

namespace engine
{
class Plan
  : public Primitive
  , public std::enable_shared_from_this<Plan>
{
  private:
    Vector3D m_normal;
    float m_planOffset;

  public:
    Plan(Vector3D normal, float planOffset);

    Vector3D getNormal() const;
    float getPlanOffset() const;

    void setNormal(Vector3D normal);
    void setPlanOffset(float planOffset);

    virtual float getYMax() const;

    virtual void generateContactWith(const std::shared_ptr<Primitive>& other, RigidBodyCollisionData& collisionData);
};
} // namespace engine
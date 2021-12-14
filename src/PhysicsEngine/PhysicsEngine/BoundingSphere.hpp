#pragma once

#include "PhysicsEngine/BoundingVolume.hpp"
#include "PhysicsEngine/BoundingPlan.hpp"

namespace engine
{
class BoundingSphere : public BoundingVolume
{
  private:
    Vector3D m_center;
    float m_radius;

  public:
    BoundingSphere(const std::vector<std::shared_ptr<Primitive>>& primitives = {});

    bool collideWithSphere(std::shared_ptr<BoundingSphere>& otherBoundingSphere);
    bool collideWithPlan(std::shared_ptr<BoundingPlan>& otherBoundingPlan);

    virtual bool collideWith(std::shared_ptr<BoundingVolume>& other);

    inline Vector3D getCenter() const {
        return m_center;
    }

    inline float getRadius() const {
        return m_radius;
    }

    void calculateCenter();
    void calculateRadius();
};
} // namespace engine

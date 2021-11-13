#pragma once

#include "PhysicsEngine/ParticleForceGenerator.hpp"

namespace engine
{
class ParticleGravity : public ParticleForceGenerator
{
  public:
    virtual void updateForce(std::shared_ptr<PhysicsObject> object, float duration);
};

} // namespace engine

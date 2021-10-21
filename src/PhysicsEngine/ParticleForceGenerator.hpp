#pragma once

#include <memory>

#include "PhysicsEngine/Particle.hpp"

class ParticleForceGenerator
{
  private:
  public:
    ParticleForceGenerator() = default;
    ~ParticleForceGenerator() = default;
    virtual void updateForce(std::shared_ptr<Particle> particle, float duration) = 0;
};

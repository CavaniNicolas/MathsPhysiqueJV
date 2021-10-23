#pragma once

#include <memory>

#include "PhysicsEngine/Particle.hpp"

class ParticleForceGenerator
{
  public:
    virtual void updateForce(std::shared_ptr<Particle> particle, float duration) = 0;
};

#pragma once

#include "PhysicsEngine/ParticleForceGenerator.hpp"

class ParticleGravity : public ParticleForceGenerator
{
  public:
    void updateForce(std::shared_ptr<Particle> particle, float duration);
};

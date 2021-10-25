#pragma once

#include "PhysicsEngine/ParticleForceGenerator.hpp"

class ParticleGravity : public ParticleForceGenerator
{
  public:
    unsigned int updateForce(std::shared_ptr<Particle> particle,
                             float duration,
                             std::vector<std::shared_ptr<ParticleContact>>& contacts,
                             unsigned int limit);
};

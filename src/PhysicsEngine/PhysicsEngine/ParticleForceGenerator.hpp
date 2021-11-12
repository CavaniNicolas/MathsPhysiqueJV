#pragma once

#include "PhysicsEngine/Particle.hpp"
#include "PhysicsEngine/ParticleContact.hpp"
#include "PhysicsEngine/ForceGenerator.hpp"

namespace engine
{
class ParticleForceGenerator
{
  public:
    virtual void updateForce(std::shared_ptr<Particle> particle, float duration) = 0;
};

} // namespace engine

#pragma once

#include "PhysicsEngine/ParticleSpring.hpp"
#include "PhysicsEngine/ParticleCable.hpp"

namespace engine
{

class CableSpring : public ParticleSpring
{
  private:
    float m_elasticityLimit;
    float m_restitution;

  public:
    CableSpring(
      std::shared_ptr<Particle> otherParticle, float k, float restLength, float elasticityLimit, float restitution);

    // apply Hook's law based on particles position
    unsigned int updateForce(std::shared_ptr<Particle> particle,
                             float duration,
                             std::vector<std::shared_ptr<ParticleContact>>& contacts,
                             unsigned int limit);
};

} // namespace engine

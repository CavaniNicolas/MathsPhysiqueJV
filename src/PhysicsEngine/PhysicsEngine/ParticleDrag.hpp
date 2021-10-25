#pragma once

#include "PhysicsEngine/ParticleForceGenerator.hpp"

namespace engine
{

class ParticleDrag : public ParticleForceGenerator
{
  private:
    // drag coefficients
    float m_k1;
    float m_k2;

  public:
    ParticleDrag(float k1, float k2);
    unsigned int updateForce(std::shared_ptr<Particle> particle,
                             float duration,
                             std::vector<std::shared_ptr<ParticleContact>>& contacts,
                             unsigned int limit);
};

} // namespace engine

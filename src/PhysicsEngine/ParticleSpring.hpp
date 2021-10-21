#pragma once

#include "PhysicsEngine/ParticleForceGenerator.hpp"

class ParticleSpring : public ParticleForceGenerator
{
  private:
    // other anchor
    std::shared_ptr<Particle> m_otherParticle;

    // Spring constant
    float m_k;

    float m_restLength;

  public:
    ParticleSpring(std::shared_ptr<Particle> otherParticle, float k, float restLength);

    // apply Hook's law based on particles position
    void updateForce(std::shared_ptr<Particle> particle, float duration);
};

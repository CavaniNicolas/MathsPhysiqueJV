#pragma once

#include "PhysicsEngine/ParticleForceGenerator.hpp"

namespace engine
{
class ParticleSpring : public ParticleForceGenerator
{
  protected:
    // other anchor
    std::shared_ptr<Particle> m_otherParticle;

    // Spring constant
    float m_k;

    float m_restLength;

  public:
    ParticleSpring(std::shared_ptr<Particle> otherParticle, float k, float restLength);

    // apply Hook's law based on particles position
    virtual void updateForce(std::shared_ptr<PhysicsObject> object, float duration);
};

} // namespace engine

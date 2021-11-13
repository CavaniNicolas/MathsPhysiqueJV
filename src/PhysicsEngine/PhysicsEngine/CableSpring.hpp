#pragma once

#include "PhysicsEngine/ParticleSpring.hpp"
#include "PhysicsEngine/ParticleCable.hpp"

namespace engine
{
class CableSpring
  : public ParticleSpring
  , public ParticleCable
{
  private:
    std::vector<std::shared_ptr<Particle>> m_linkedParticles;

  public:
    CableSpring(
      std::shared_ptr<Particle> otherParticle, float k, float restLength, float elasticityLimit, float restitution);

    // apply Hook's law based on particles position
    virtual void updateForce(std::shared_ptr<PhysicsObject> object, float duration);

    // Fill ParticleContact with information from particles and contact generator
    virtual unsigned int addContact(std::vector<std::shared_ptr<ParticleContact>>& contacts, unsigned int limit);
};

} // namespace engine

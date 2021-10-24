#include "PhysicsEngine/CableSpring.hpp"

CableSpring::CableSpring(
  std::shared_ptr<Particle> otherParticle, float k, float restLength, float elasticityLimit, float restitution):
  ParticleSpring(otherParticle, k, restLength),
  m_elasticityLimit(elasticityLimit), m_restitution(restitution)
{}

// apply Hook's law based on particles position
unsigned int CableSpring::updateForce(std::shared_ptr<Particle> particle,
                              float duration,
                              std::vector<std::shared_ptr<ParticleContact>>& contacts,
                              unsigned int limit)
{
    float distance = (m_otherParticle->getPosition() - particle->getPosition()).getNorm();
    if (distance > m_elasticityLimit) {
        ParticleCable cable = ParticleCable(particle, m_otherParticle, m_elasticityLimit, m_restitution);
        return cable.addContact(contacts, limit);
    }
    else
    {
        ParticleSpring::updateForce(particle, duration, contacts, limit);
        return 0;
    }
}
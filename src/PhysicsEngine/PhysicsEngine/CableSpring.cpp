#include "PhysicsEngine/CableSpring.hpp"

namespace engine
{
CableSpring::CableSpring(
  std::shared_ptr<Particle> otherParticle, float k, float restLength, float elasticityLimit, float restitution):
  ParticleSpring(otherParticle, k, restLength), ParticleCable(otherParticle, elasticityLimit, restitution)
{
}

// apply Hook's law based on particles position
void CableSpring::updateForce(std::shared_ptr<Particle> particle, float duration)
{
    m_linkedParticles.push_back(particle);
    ParticleSpring::updateForce(particle, duration);
}

// Fill ParticleContact with information from particles and contact generator
unsigned int CableSpring::addContact(std::vector<std::shared_ptr<ParticleContact>>& contacts, unsigned int limit)
{
    int contactNb = 0;
    for (auto particle : m_linkedParticles) {
        setParticleB(particle);
        contactNb += ParticleCable::addContact(contacts, limit - contactNb);
    }
    m_linkedParticles.clear();

    return contactNb;
}

} // namespace engine

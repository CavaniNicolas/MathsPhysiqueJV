#include "PhysicsEngine/CableSpring.hpp"

namespace engine
{
CableSpring::CableSpring(
  std::shared_ptr<Particle> otherParticle, float k, float restLength, float elasticityLimit, float restitution):
  ParticleSpring(otherParticle, k, restLength), ParticleCable(otherParticle, elasticityLimit, restitution)
{
}

// apply Hook's law based on particles position
void CableSpring::updateForce(std::shared_ptr<PhysicsObject> object, float duration)
{
    if (std::shared_ptr<Particle> particle = std::dynamic_pointer_cast<Particle>(object)) {
        m_linkedParticles.push_back(particle);
        ParticleSpring::updateForce(particle, duration);
    }
    else
    {
        std::cerr << "Tried to apply a ParticleForce to a non particle object." << std::endl;
        exit(EXIT_FAILURE);
    }
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

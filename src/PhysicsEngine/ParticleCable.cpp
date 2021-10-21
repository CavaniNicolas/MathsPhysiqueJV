#include "ParticleCable.hpp"

ParticleCable::ParticleCable(std::shared_ptr<Particle> particleA, std::shared_ptr<Particle> particleB, float maxlength, float restitution) : 
    ParticleLink(particleA, particleB), m_maxlength(maxlength), m_restitution(restitution) 
{}

// Fill ParticleContact with information from particles and contact generator
unsigned int ParticleCable::addContact(std::shared_ptr<std::vector<std::shared_ptr<ParticleContact>>> contacts,
                        unsigned int limit) const
{
    // TODO
    return -1;
}
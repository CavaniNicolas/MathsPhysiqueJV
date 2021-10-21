#include "ParticleCable.hpp"

ParticleCable::ParticleCable(std::shared_ptr<Particle> particleA, std::shared_ptr<Particle> particleB, float maxlength, float restitution) : 
    ParticleLink(particleA, particleB), m_maxlength(maxlength), m_restitution(restitution) 
{}

// Fill ParticleContact with information from particles and contact generator
unsigned int ParticleCable::addContact(std::shared_ptr<std::vector<std::shared_ptr<ParticleContact>>> contacts,
                        unsigned int limit) const
{
    float penetrationDistance = currentLength() - m_maxlength;
    if (penetrationDistance > 0) {
        if(limit >= 2)
        {
            Vector3D normalA = (m_particle[1]->getPosition() - m_particle[0]->getPosition()).normalize();
            contacts->push_back(std::make_shared<ParticleContact>(m_particle[0], nullptr, m_restitution, penetrationDistance, normalA));
            contacts->push_back(std::make_shared<ParticleContact>   (m_particle[1], nullptr, m_restitution, penetrationDistance, normalA * -1));
            return 2;
        }
    }
    return 0;
}
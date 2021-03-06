#include "ParticleCable.hpp"

namespace engine
{
ParticleCable::ParticleCable(std::shared_ptr<Particle> particleA,
                             std::shared_ptr<Particle> particleB,
                             float maxlength,
                             float restitution):
  ParticleLink(particleA, particleB), m_maxlength(maxlength), m_restitution(restitution)
{
}

ParticleCable::ParticleCable(std::shared_ptr<Particle> particleA, float maxlength, float restitution):
  ParticleLink(particleA), m_maxlength(maxlength), m_restitution(restitution)
{
}

// Fill ParticleContact with information from particles and contact generator
unsigned int ParticleCable::addContact(std::vector<std::shared_ptr<ParticleContact>>& contacts, unsigned int limit)
{
    float totalGap = currentLength() - m_maxlength;
    if(totalGap > 0)
    {
        if(limit >= 2)
        {
            Vector3D normalA = (m_particle[1]->getPosition() - m_particle[0]->getPosition()).normalize();
            float penetrationA = totalGap / 2 + m_particle[0]->getRadius();
            float penetrationB = totalGap / 2 + m_particle[1]->getRadius();
            contacts.push_back(
              std::make_shared<ParticleContact>(m_particle[0], nullptr, m_restitution, penetrationA, normalA));
            contacts.push_back(
              std::make_shared<ParticleContact>(m_particle[1], nullptr, m_restitution, penetrationB, normalA * -1));
            return 2;
        }
    }
    return 0;
}

} // namespace engine

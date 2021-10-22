#include "ParticleRod.hpp"


ParticleRod::ParticleRod(std::shared_ptr<Particle> particleA, std::shared_ptr<Particle> particleB, float length):
  ParticleLink(particleA, particleB),
  m_length(length)
{}


unsigned int ParticleRod::addContact(std::vector<std::shared_ptr<ParticleContact>>& contacts,
                                     unsigned int limit) const
{
    float totalGap = currentLength() - m_length;
    if(totalGap != 0)
    {
        if(limit >= 2)
        {
            Vector3D normalA = (m_particle[1]->getPosition() - m_particle[0]->getPosition()).normalize();
            float penetrationA = totalGap / 2 + m_particle[0]->getRadius();
            float penetrationB = totalGap / 2 + m_particle[1]->getRadius();
            contacts.push_back(std::make_shared<ParticleContact>(m_particle[0], nullptr, 1, penetrationA, normalA));
            contacts.push_back(std::make_shared<ParticleContact>(m_particle[1], nullptr, 1, penetrationB, normalA * -1));
            return 2;
        }
    }
    return 0;
}
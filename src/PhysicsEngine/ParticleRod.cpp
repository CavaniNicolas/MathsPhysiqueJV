#include "ParticleRod.hpp"


ParticleRod::ParticleRod(std::shared_ptr<Particle> particleA, std::shared_ptr<Particle> particleB, float length):
  ParticleLink(particleA, particleB),
  m_length(length)
{}


unsigned int ParticleRod::addContact(std::shared_ptr<std::vector<std::shared_ptr<ParticleContact>>> contacts,
                                     unsigned int limit) const
{
    float penetrationDistance = currentLength() - m_length;
    if (penetrationDistance != 0) {
        if(limit >= 2)
        {
            Vector3D normalA = (m_particle[1]->getPosition() - m_particle[0]->getPosition()).normalize();
            contacts->push_back(std::make_shared<ParticleContact>(m_particle[0], nullptr, 1, penetrationDistance, normalA));
            contacts->push_back(std::make_shared<ParticleContact>(m_particle[1], nullptr, 1, penetrationDistance, normalA * -1));
            return 2;
        }
    }
    return 0;
}
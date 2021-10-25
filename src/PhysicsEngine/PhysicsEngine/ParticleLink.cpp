#include "ParticleLink.hpp"

namespace engine
{

ParticleLink::ParticleLink(std::shared_ptr<Particle> particleA, std::shared_ptr<Particle> particleB):
  m_particle({particleA, particleB})
{
}

ParticleLink ::~ParticleLink()
{
    m_particle.clear();
}

// return the length of the link
float ParticleLink::currentLength() const
{
    return (m_particle[0]->getPosition() - m_particle[1]->getPosition()).getNorm();
}

} // namespace engine

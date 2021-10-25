
#include "ParticleSpring.hpp"

ParticleSpring::ParticleSpring(std::shared_ptr<Particle> otherParticle, float k, float restLength):
  m_otherParticle(otherParticle), m_k(k), m_restLength(restLength)
{
}

// apply Hook's law based on particles position
unsigned int ParticleSpring::updateForce(std::shared_ptr<Particle> particle,
                                         float duration,
                                         std::vector<std::shared_ptr<ParticleContact>>& contacts,
                                         unsigned int limit)
{
    Vector3D springLength = particle->getPosition() - m_otherParticle->getPosition();

    Vector3D force = springLength.normalize() * -m_k * (springLength.getNorm() - m_restLength);

    if(springLength.getNorm() - m_restLength != 0)
    {
        if(particle->isResting())
        {
            particle->setResting(false);
        }
        if(m_otherParticle->isResting())
        {
            m_otherParticle->setResting(false);
        }
    }

    particle->setAcceleration(particle->getAcceleration() + force * particle->getInverseMass());
    m_otherParticle->setAcceleration(m_otherParticle->getAcceleration() - force * m_otherParticle->getInverseMass());

    return 0;
}

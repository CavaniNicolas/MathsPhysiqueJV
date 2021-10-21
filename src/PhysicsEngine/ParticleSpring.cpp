
#include "ParticleSpring.hpp"

ParticleSpring::ParticleSpring(std::shared_ptr<Particle> otherParticle, float k, float restLength):
  m_otherParticle(otherParticle), m_k(k), m_restLength(restLength)
{
}

// apply Hook's law based on particles position
void ParticleSpring::updateForce(std::shared_ptr<Particle> particle, float duration)
{
    Vector3D springLength = particle->getPosition() - m_otherParticle->getPosition();

    Vector3D force = springLength.normalize() * -m_k * (springLength.getNorm() - m_restLength);

    particle->setAcceleration(particle->getAcceleration() + force * particle->getInverseMass());
}


#include "PhysicsEngine/ParticleAnchoredSpring.hpp"

ParticleAnchoredSpring::ParticleAnchoredSpring(Vector3D anchor, float k, float restLength):
  m_anchor(anchor), m_k(k), m_restLength(restLength)
{
}

void ParticleAnchoredSpring::updateForce(std::shared_ptr<Particle> particle, float duration)
{
    Vector3D d = particle->getPosition() - m_anchor;

    Vector3D force = d.normalize() * -m_k * (d.getNorm() - m_restLength);

    if (d.getNorm() - m_restLength != 0) {
        if (particle->isResting()) {
            particle->setResting(false);
        }
    }

    particle->setAcceleration(particle->getAcceleration() + force * particle->getInverseMass());
}

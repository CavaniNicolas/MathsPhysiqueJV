
#include "PhysicsEngine/ParticleAnchoredSpring.hpp"

ParticleAnchoredSpring::ParticleAnchoredSpring(Vector3D anchor, float k, float restLength):
  m_anchor(anchor), m_k(k), m_restLength(restLength)
{
}

unsigned int ParticleAnchoredSpring::updateForce(std::shared_ptr<Particle> particle,
                                                 float duration,
                                                 std::vector<std::shared_ptr<ParticleContact>>& contacts,
                                                 unsigned int limit)
{
    Vector3D d = particle->getPosition() - m_anchor;

    Vector3D force = d.normalize() * -m_k * (d.getNorm() - m_restLength);

    if(d.getNorm() - m_restLength != 0)
    {
        if(particle->isResting())
        {
            particle->setResting(false);
        }
    }

    particle->setAcceleration(particle->getAcceleration() + force * particle->getInverseMass());
    return 0;
}


#include "PhysicsEngine/ParticleBungeeSpring.hpp"

namespace engine
{
ParticleBungeeSpring::ParticleBungeeSpring(Vector3D anchor, float k, float restLength):
  m_anchor(anchor), m_k(k), m_restLength(restLength)
{
}

void ParticleBungeeSpring::updateForce(std::shared_ptr<PhysicsObject> object, float duration)
{
    auto particle = checkParticle(object);

    Vector3D d = particle->getPosition() - m_anchor;
    if(d.getNorm() > m_restLength)
    {
        Vector3D force = d.normalize() * -m_k * (d.getNorm() - m_restLength);
        particle->setAcceleration(particle->getAcceleration() + force * particle->getInverseMass());

        if(particle->isResting())
        {
            particle->setResting(false);
        }
    }
}

} // namespace engine

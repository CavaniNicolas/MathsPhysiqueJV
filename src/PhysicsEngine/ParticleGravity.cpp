
#include "PhysicsEngine/ParticleGravity.hpp"

void ParticleGravity::updateForce(std::shared_ptr<Particle> particle, float duration)
{
    //    Vector3D force = m_gravity * particle->getMass();
    //    particle->setAcceleration(particle->getAcceleration() + force * particle->getInverseMass());
    particle->setAcceleration(particle->getAcceleration() + m_gravity);
}

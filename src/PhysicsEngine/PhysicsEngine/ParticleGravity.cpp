
#include "PhysicsEngine/ParticleGravity.hpp"

unsigned int ParticleGravity::updateForce(std::shared_ptr<Particle> particle,
                                  float duration,
                                  std::vector<std::shared_ptr<ParticleContact>>& contacts,
                                  unsigned int limit)
{
    if(!particle->isResting())
    {
        Vector3D gravity(0, -particle->getG(), 0);

        //    Vector3D force = gravity * particle->getMass();
        //    particle->setAcceleration(particle->getAcceleration() + force * particle->getInverseMass());
        particle->setAcceleration(particle->getAcceleration() + gravity);
    }
    return 0;
}

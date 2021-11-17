
#include "PhysicsEngine/ParticleGravity.hpp"

namespace engine
{
void ParticleGravity::updateForce(std::shared_ptr<PhysicsObject> object, float duration)
{
    auto particle = checkParticle(object);

    if(!particle->isResting())
    {
        Vector3D gravity(0, -particle->getG(), 0);

        //    Vector3D force = gravity * particle->getMass();
        //    particle->setAcceleration(particle->getAcceleration() + force * particle->getInverseMass());
        particle->setAcceleration(particle->getAcceleration() + gravity);
    }
}

} // namespace engine


#include "PhysicsEngine/ParticleGravity.hpp"

namespace engine
{
void ParticleGravity::updateForce(std::shared_ptr<PhysicsObject> object, float duration)
{
    if(std::shared_ptr<Particle> particle = std::dynamic_pointer_cast<Particle>(object))
    {
        if(!particle->isResting())
        {
            Vector3D gravity(0, -particle->getG(), 0);

            //    Vector3D force = gravity * particle->getMass();
            //    particle->setAcceleration(particle->getAcceleration() + force * particle->getInverseMass());
            particle->setAcceleration(particle->getAcceleration() + gravity);
        }
    }
    else
    {
        std::cerr << "Tried to apply a ParticleForce to a non particle object." << std::endl;
        exit(EXIT_FAILURE);
    }
}

} // namespace engine

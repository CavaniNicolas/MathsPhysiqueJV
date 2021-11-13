
#include "PhysicsEngine/ParticleDrag.hpp"
#include "PhysicsEngine/Vector3D.hpp"

namespace engine
{
ParticleDrag::ParticleDrag(float k1, float k2): m_k1(k1), m_k2(k2) {}

void ParticleDrag::updateForce(std::shared_ptr<PhysicsObject> object, float duration)
{
    if(std::shared_ptr<Particle> particle = std::dynamic_pointer_cast<Particle>(object))
    {
        if(!particle->isResting())
        {
            Vector3D velocity = particle->getVelocity();
            Vector3D dragForce =
              velocity.normalize() * -(velocity.getNorm() * m_k1 + m_k2 * pow(velocity.getNorm(), 2));

            particle->setAcceleration(particle->getAcceleration() + dragForce * particle->getInverseMass());
        }
    }
    else
    {
        std::cerr << "Tried to apply a ParticleForce to a non particle object." << std::endl;
        exit(EXIT_FAILURE);
    }
}

} // namespace engine


#include "PhysicsEngine/ParticleDrag.hpp"
#include "PhysicsEngine/Vector3D.hpp"

namespace engine
{
ParticleDrag::ParticleDrag(float k1, float k2): m_k1(k1), m_k2(k2) {}

void ParticleDrag::updateForce(std::shared_ptr<PhysicsObject> object, float duration)
{
    auto particle = checkParticle(object);

    if(!particle->isResting())
    {
        Vector3D velocity = particle->getVelocity();
        Vector3D dragForce = velocity.normalize() * -(velocity.getNorm() * m_k1 + m_k2 * pow(velocity.getNorm(), 2));

        particle->setAcceleration(particle->getAcceleration() + dragForce * particle->getInverseMass());
    }
}

} // namespace engine

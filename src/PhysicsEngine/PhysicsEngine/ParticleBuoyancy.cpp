#pragma once

#include "PhysicsEngine/ParticleBuoyancy.hpp"

namespace engine
{
ParticleBuoyancy::ParticleBuoyancy(float maxDepth, float volume, float waterHeight, float liquidDensity):
  ParticleForceGenerator(),
  m_maxDepth(maxDepth),
  m_volume(volume),
  m_waterHeight(waterHeight),
  m_liquidDensity(liquidDensity)
{
}

// Apply Buoyancy based on particle position
void ParticleBuoyancy::updateForce(std::shared_ptr<PhysicsObject> object, float duration)
{
    auto particle = checkParticle(object);

    float submergedQuantity = (particle->getPosition().getX() - m_waterHeight - m_maxDepth) / 2 * m_maxDepth;
    Vector3D force = Vector3D();
    if(submergedQuantity <= 0)
    {
        // The particle is not submerged at all
    }
    else if(submergedQuantity < 1)
    {
        // The particle is partially submerged
        force.setY(submergedQuantity * m_volume * m_liquidDensity);

        if(particle->isResting())
        {
            particle->setResting(false);
        }
    }
    else
    {
        // The particle is totally submerged
        force.setY(m_volume * m_liquidDensity);

        if(particle->isResting())
        {
            particle->setResting(false);
        }
    }
    particle->setAcceleration(particle->getAcceleration() + force * particle->getInverseMass());
}
} // namespace engine

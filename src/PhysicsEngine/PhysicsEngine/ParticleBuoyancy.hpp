#pragma once

#include "PhysicsEngine/ParticleForceGenerator.hpp"

namespace engine
{
class ParticleBuoyancy : public ParticleForceGenerator
{
  private:
    // Particle properties
    float m_maxDepth;
    float m_volume;

    // Effect properties
    float m_waterHeight;
    float m_liquidDensity;

  public:
    ParticleBuoyancy(float maxDepth, float volume, float waterHeight, float liquidDensity = 1);

    // Apply Buoyancy based on particle position
    virtual void updateForce(std::shared_ptr<PhysicsObject> object, float duration);
};

} // namespace engine

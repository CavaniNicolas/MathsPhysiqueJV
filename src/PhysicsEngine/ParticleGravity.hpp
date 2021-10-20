#pragma once

#include "PhysicsEngine/ParticleForceGenerator.hpp"

class ParticleGravity : public ParticleForceGenerator
{
  private:
    Vector3D m_gravity;

  public:
    void updateForce(std::shared_ptr<Particle> particle, float duration);
};

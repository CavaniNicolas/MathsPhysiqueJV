#pragma once

#include "PhysicsEngine/ParticleForceGenerator.hpp"

class ParticleAnchoredSpring : public ParticleForceGenerator
{
  private:
    // Other anchor
    Vector3D m_anchor;

    // Spring constant
    float m_k;
    float m_restLength;

  public:
    ParticleAnchoredSpring(Vector3D anchor, float k, float restLength);

    void updateForce(std::shared_ptr<Particle> particle, float duration);
};

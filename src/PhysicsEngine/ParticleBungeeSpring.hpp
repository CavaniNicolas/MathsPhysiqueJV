#pragma once

#include "PhysicsEngine/ParticleForceGenerator.hpp"

class ParticleBungeeSpring : public ParticleForceGenerator
{
  private:
    // can be another particle or a fixed anchor
    Vector3D m_anchor;

    float m_k;

    float m_restLength;

  public:
    ParticleBungeeSpring(Vector3D anchor, float k, float restLength);
    void UpdateForce(std::shared_ptr<Particle> particle, float duration);
};
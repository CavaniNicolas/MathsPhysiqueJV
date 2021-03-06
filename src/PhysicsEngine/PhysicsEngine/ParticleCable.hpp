#pragma once

#include "ParticleLink.hpp"

namespace engine
{
class ParticleCable : public ParticleLink
{
  public:
    // a contact will be generated if the distance
    // between particles is larger than maxlength
    float m_maxlength;

    // bounciness of the cable
    float m_restitution;

    ParticleCable(std::shared_ptr<Particle> particleA,
                  std::shared_ptr<Particle> particleB,
                  float maxlength,
                  float restitution);

    ParticleCable(std::shared_ptr<Particle> particleA, float maxlength, float restitution);

    // Fill ParticleContact with information from particles and contact generator
    virtual unsigned int addContact(std::vector<std::shared_ptr<ParticleContact>>& contacts, unsigned int limit);
};

} // namespace engine

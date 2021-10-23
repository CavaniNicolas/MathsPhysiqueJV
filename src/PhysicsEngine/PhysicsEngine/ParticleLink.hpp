#pragma once

#include "ParticleContactGenerator.hpp"

class ParticleLink : public ParticleContactGenerator
{
  protected:
    // Linked particles
    std::vector<std::shared_ptr<Particle>> m_particle;

  public:
    ParticleLink(std::shared_ptr<Particle> particleA, std::shared_ptr<Particle> particleB);
    ~ParticleLink();

    // return the length of the link
    float currentLength() const;

    // Take a pointer to an array of contact and the number of contact left to be generated
    unsigned int addContact(std::vector<std::shared_ptr<ParticleContact>>& contacts, unsigned int limit) const = 0;
};
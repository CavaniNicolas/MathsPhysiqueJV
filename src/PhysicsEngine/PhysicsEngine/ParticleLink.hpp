#pragma once

#include "PhysicsEngine/ParticleContactGenerator.hpp"

namespace engine
{

class ParticleLink : public ParticleContactGenerator
{
  protected:
    // Linked particles
    std::vector<std::shared_ptr<Particle>> m_particle;

  public:
    ParticleLink(std::shared_ptr<Particle> particleA, std::shared_ptr<Particle> particleB = nullptr);
    ~ParticleLink();

    void setParticleB(std::shared_ptr<Particle> particleB);

    // return the length of the link
    float currentLength() const;

    // Take a pointer to an array of contact and the number of contact left to be generated
    virtual unsigned int addContact(std::vector<std::shared_ptr<ParticleContact>>& contacts, unsigned int limit) = 0;
};

} // namespace engine

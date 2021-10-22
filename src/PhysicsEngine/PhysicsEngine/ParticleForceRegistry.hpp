#pragma once

#include "PhysicsEngine/ParticleForceGenerator.hpp"

class ParticleForceRegistry
{
  private:
    struct ParticleForceEntry
    {
        std::shared_ptr<Particle> particle;
        std::shared_ptr<ParticleForceGenerator> forceGenerator;
    };

    using Registry = std::vector<ParticleForceEntry>;
    Registry m_registry;

  public:
    // Constructors
    ParticleForceRegistry(Registry registry = {});
    ParticleForceRegistry(const ParticleForceRegistry& other);
    // Destructor
    ~ParticleForceRegistry();

    ParticleForceRegistry& operator=(const ParticleForceRegistry& other);

    // Setters
    void addEntry(std::shared_ptr<Particle> particle, std::shared_ptr<ParticleForceGenerator> forceGenerator);
    void setRegistry(Registry newRegistry);

    // Getters
    Registry getRegistry();

    void updateForce(float duration);
};

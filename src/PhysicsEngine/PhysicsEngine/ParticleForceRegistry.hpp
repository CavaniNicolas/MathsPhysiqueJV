#pragma once

#include "PhysicsEngine/ParticleForceGenerator.hpp"

namespace engine
{

class ParticleForceRegistry
{
  private:
    struct ParticleForceEntry
    {
        std::weak_ptr<Particle> particle;
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

    unsigned int updateForce(float duration,
                             std::vector<std::shared_ptr<ParticleContact>>& contacts,
                             unsigned int limit);
};

} // namespace engine

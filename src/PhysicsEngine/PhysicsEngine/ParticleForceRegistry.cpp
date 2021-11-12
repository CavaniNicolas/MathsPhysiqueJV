
#include "PhysicsEngine/ParticleForceRegistry.hpp"
#include "PhysicsEngine/ParticleContact.hpp"

namespace engine
{
ParticleForceRegistry::ParticleForceRegistry(Registry registry): m_registry(registry) {}

ParticleForceRegistry::~ParticleForceRegistry()
{
    m_registry.clear();
}

ParticleForceRegistry::ParticleForceRegistry(const ParticleForceRegistry& other)
{
    m_registry = other.m_registry;
}

ParticleForceRegistry& ParticleForceRegistry::operator=(const ParticleForceRegistry& other)
{
    m_registry = other.m_registry;
    return *this;
}

void ParticleForceRegistry::addEntry(std::shared_ptr<Particle> particle,
                                     std::shared_ptr<ParticleForceGenerator> forceGenerator)
{
    m_registry.push_back({particle, forceGenerator});
}

void ParticleForceRegistry::setRegistry(Registry newRegistry)
{
    m_registry.clear();
    m_registry = newRegistry;
}

ParticleForceRegistry::Registry ParticleForceRegistry::getRegistry()
{
    return m_registry;
}

void ParticleForceRegistry::updateForce(float duration)
{
    unsigned int createdContacts = 0;
    for(const auto& entry: m_registry)
    {
        // creates a shared_ptr that manages the referenced object by the weak_ptr
        std::shared_ptr<Particle> particle = entry.particle.lock();

        entry.forceGenerator->updateForce(particle, duration);
    }
}

} // namespace engine

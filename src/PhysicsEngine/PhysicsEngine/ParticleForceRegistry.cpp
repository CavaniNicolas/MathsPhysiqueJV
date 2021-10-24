
#include "PhysicsEngine/ParticleForceRegistry.hpp"
#include "PhysicsEngine/ParticleContact.hpp"

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

unsigned int ParticleForceRegistry::updateForce(float duration,
                                                std::vector<std::shared_ptr<ParticleContact>>& contacts,
                                                unsigned int limit)
{
    unsigned int createdContacts = 0;
    for(const auto& entry: m_registry)
    {
        createdContacts += entry.forceGenerator->updateForce(entry.particle, duration, contacts, limit);
    }
    return createdContacts;
}

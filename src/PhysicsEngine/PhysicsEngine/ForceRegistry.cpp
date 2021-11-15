
#include "PhysicsEngine/ForceRegistry.hpp"
#include "PhysicsEngine/ParticleContact.hpp"

namespace engine
{
ForceRegistry::ForceRegistry(Registry registry): m_registry(registry) {}

ForceRegistry::~ForceRegistry()
{
    m_registry.clear();
}

ForceRegistry::ForceRegistry(const ForceRegistry& other)
{
    m_registry = other.m_registry;
}

ForceRegistry& ForceRegistry::operator=(const ForceRegistry& other)
{
    m_registry = other.m_registry;
    return *this;
}

void ForceRegistry::addEntry(std::shared_ptr<PhysicsObject> object, std::shared_ptr<ForceGenerator> forceGenerator)
{
    m_registry.push_back({object, forceGenerator});
}

void ForceRegistry::setRegistry(Registry newRegistry)
{
    m_registry.clear();
    m_registry = newRegistry;
}

ForceRegistry::Registry ForceRegistry::getRegistry()
{
    return m_registry;
}

void ForceRegistry::updateForce(float duration)
{
    for(const auto& entry: m_registry)
    {
        // creates a shared_ptr that manages the referenced object by the weak_ptr
        std::shared_ptr<PhysicsObject> object = entry.object.lock();

        entry.forceGenerator->updateForce(object, duration);
    }
}

} // namespace engine

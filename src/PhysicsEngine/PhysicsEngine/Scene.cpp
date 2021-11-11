
#include "PhysicsEngine/Scene.hpp"

namespace engine
{

Scene::Scene(std::vector<std::shared_ptr<PhysicsObject>> objects,
             ParticleForceRegistry forcesRegistry,
             std::vector<std::shared_ptr<ParticleContactGenerator>> particleContactGenerators,
             int maxContactsPerIteration):
  m_particleForceRegistry(forcesRegistry),
  m_physicsObject(objects),
  m_particleContactGenerators(particleContactGenerators),
  m_maxContactsPerIteration(maxContactsPerIteration)
{
    m_contactResolver = ParticleContactResolver();
    m_contactArray = {};
}

Scene::Scene(const Scene& other)
{
    m_physicsObject = other.m_physicsObject;
    m_particleForceRegistry = other.m_particleForceRegistry;
    m_particleContactGenerators = other.m_particleContactGenerators;
    m_maxContactsPerIteration = other.m_maxContactsPerIteration;
    m_contactResolver = ParticleContactResolver();
    m_contactArray = {};
}

Scene& Scene::operator=(const Scene& other)
{
    m_physicsObject = other.m_physicsObject;
    m_particleForceRegistry = other.m_particleForceRegistry;
    m_particleContactGenerators = other.m_particleContactGenerators;
    m_maxContactsPerIteration = other.m_maxContactsPerIteration;
    return *this;
}

std::vector<std::shared_ptr<PhysicsObject>> Scene::getParticles() const
{
    return m_physicsObject;
}

// std::vector<Particle> Scene::getParticlesSynchronized() {
//	m_particlesMutex.lock();
//	std::vector<Particle> ret = getParticles();
//	m_particlesMutex.unlock();
//	return ret;
// }

void Scene::addParticle(std::shared_ptr<Particle> particle)
{
    m_physicsObject.push_back(particle);
}

void Scene::addParticleForce(std::shared_ptr<Particle> particle, std::shared_ptr<ParticleForceGenerator> forceGenerator)
{
    m_particleForceRegistry.addEntry(particle, forceGenerator);
}

void Scene::addForce(std::shared_ptr<ParticleForceGenerator> forceGenerator)
{
    for(auto& object: m_physicsObject)
    {
        if (std::shared_ptr<Particle> particle = std::dynamic_pointer_cast<Particle>(object)) {
            m_particleForceRegistry.addEntry(particle, forceGenerator);
        }
    }
}

void Scene::addParticleContactGenerator(std::shared_ptr<ParticleContactGenerator> contactGenerator)
{
    m_particleContactGenerators.push_back(contactGenerator);
}

void Scene::integrateAll(float deltaT)
{
    unsigned int contacts = m_maxContactsPerIteration;
    // We move the particles
    for(auto& object: m_physicsObject)
    {
        object->integratePosition(deltaT);
    }
    contacts -= m_particleForceRegistry.updateForce(deltaT, m_contactArray, contacts);
    for(auto& object: m_physicsObject)
    {
        object->integrateVelocity(deltaT);
    }
    // We check for contacts
    for(auto& contactGenerator: m_particleContactGenerators)
    {
        contacts -= contactGenerator->addContact(m_contactArray, contacts);
    }
    // We resolve the found contacts
    m_contactResolver.resolveContacts(m_contactArray);
    // We processed every contact, we can now clear the contact
    // array to fill it once again during the next iteration
    m_contactArray.clear();
}

} // namespace engine

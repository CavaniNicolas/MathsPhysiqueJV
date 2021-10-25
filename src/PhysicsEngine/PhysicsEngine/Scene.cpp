
#include "PhysicsEngine/Scene.hpp"

namespace engine
{

Scene::Scene(std::vector<std::shared_ptr<Particle>> particles,
             ParticleForceRegistry forcesRegistry,
             std::vector<std::shared_ptr<ParticleContactGenerator>> contactGenerators,
             int maxContactsPerIteration):
  m_forcesRegistry(forcesRegistry),
  m_particles(particles),
  m_contactGenerators(contactGenerators),
  m_maxContactsPerIteration(maxContactsPerIteration)
{
    m_contactResolver = ParticleContactResolver();
    m_contactArray = {};
}

Scene::Scene(const Scene& other)
{
    m_particles = other.m_particles;
    m_forcesRegistry = other.m_forcesRegistry;
    m_contactGenerators = other.m_contactGenerators;
    m_maxContactsPerIteration = other.m_maxContactsPerIteration;
    m_contactResolver = ParticleContactResolver();
    m_contactArray = {};
}

Scene& Scene::operator=(const Scene& other)
{
    m_particles = other.m_particles;
    m_forcesRegistry = other.m_forcesRegistry;
    m_contactGenerators = other.m_contactGenerators;
    m_maxContactsPerIteration = other.m_maxContactsPerIteration;
    return *this;
}

std::vector<std::shared_ptr<Particle>> Scene::getParticles() const
{
    return m_particles;
}

// std::vector<Particle> Scene::getParticlesSynchronized() {
//	m_particlesMutex.lock();
//	std::vector<Particle> ret = getParticles();
//	m_particlesMutex.unlock();
//	return ret;
// }

// TO CHECK
void Scene::setParticles(std::vector<std::shared_ptr<Particle>> particles)
{
    m_particles.clear();
    m_particles = particles;
}

void Scene::addParticle(std::shared_ptr<Particle> particle)
{
    m_particles.push_back(particle);
}

void Scene::addForce(std::shared_ptr<Particle> particle, std::shared_ptr<ParticleForceGenerator> forceGenerator)
{
    m_forcesRegistry.addEntry(particle, forceGenerator);
}

void Scene::addForce(std::shared_ptr<ParticleForceGenerator> forceGenerator)
{
    for(auto& particle: m_particles)
    {
        m_forcesRegistry.addEntry(particle, forceGenerator);
    }
}

void Scene::addContactGenerator(std::shared_ptr<ParticleContactGenerator> contactGenerator)
{
    m_contactGenerators.push_back(contactGenerator);
}

void Scene::integrateAll(float deltaT)
{
    unsigned int contacts = m_maxContactsPerIteration;
    // We move the particles
    for(auto& particle: m_particles)
    {
        particle->integratePosition(deltaT);
    }
    contacts -= m_forcesRegistry.updateForce(deltaT, m_contactArray, contacts);
    for(auto& particle: m_particles)
    {
        particle->integrateVelocity(deltaT);
    }
    // We check for contacts
    for(auto& contactGenerator: m_contactGenerators)
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

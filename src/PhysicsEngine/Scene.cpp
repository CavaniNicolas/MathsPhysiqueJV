
#include "PhysicsEngine/Scene.hpp"

Scene::Scene(std::vector<std::shared_ptr<Particle>> particles, ParticleForceRegistry forcesRegistry):
  m_forcesRegistry(forcesRegistry), m_particles(particles)
{
}

Scene::Scene(const Scene& other)
{
    m_particles = other.m_particles;
    m_forcesRegistry = other.m_forcesRegistry;
}

Scene& Scene::operator=(const Scene& other)
{
    m_particles = other.m_particles;
    m_forcesRegistry = other.m_forcesRegistry;
    return *this;
}

std::vector<Particle> Scene::getParticles() const
{
    std::vector<Particle> ret;
    for(auto const& particle: m_particles)
    {
        ret.push_back(*particle);
    }
    return ret;
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

void Scene::integrateAll(float deltaT)
{
    for(std::shared_ptr<Particle> particle: m_particles)
    {
        particle->integratePosition(deltaT);
    }
    m_forcesRegistry.updateForce(deltaT);
    for(std::shared_ptr<Particle> particle: m_particles)
    {
        particle->integrateVelocity(deltaT);
    }
}

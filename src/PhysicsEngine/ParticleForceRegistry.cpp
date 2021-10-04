#include "ParticleForceRegistry.hpp"

ParticleForceRegistry::ParticleForceRegistry(Registry registry) : m_registry(registry) { }

ParticleForceRegistry::~ParticleForceRegistry() {
	m_registry.clear();
}

void ParticleForceRegistry::addEntry(Particle* particle, ParticleForceGenerator* forceGenerator) {
	m_registry.push_back({ particle, forceGenerator });
}

void ParticleForceRegistry::setRegistry(Registry newRegistry) {
	m_registry.clear();
	m_registry = newRegistry;
}

ParticleForceRegistry::Registry ParticleForceRegistry::getRegistry() {
	return m_registry;
}

void ParticleForceRegistry::updateForce(float duration) {
	for (ParticleForceEntry entry : m_registry) {
		entry.forceGenerator->updateForce(entry.particle, duration);
	}
}
#include "Scene.hpp"

Scene::Scene(std::vector<Particle*> particles) {
	m_particles = particles;
}

Scene::Scene(Scene& other) {
	m_particles = other.getParticles();
}

Scene& Scene::operator=(const Scene& other) {
	m_particles = other.getParticles();
	return *this;
}

std::vector<Particle*> Scene::getParticles() const {
	return m_particles;
}

//TO CHECK
void Scene::setParticles(std::vector<Particle*> particles) {
	m_particles.clear();
	m_particles = particles;
}

void Scene::addParticle(Particle* particle) {
	m_particles.push_back(particle);
}

void Scene::integrateAll() {
	for (Particle* particle : m_particles) {
		particle->integrate();
	}
}
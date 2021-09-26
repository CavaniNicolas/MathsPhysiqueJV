#include "../headers/Scene.hpp"

Scene::Scene(std::vector<Particle*> particles) {
	m_particles = particles;
}

Scene::Scene(std::vector<Projectile*> projectiles) {
	for (Projectile* projectile : projectiles) {
		m_particles.push_back(projectile);
	}
}

Scene::Scene(const Scene& other) {
	std::vector<Particle> otherParticles = other.getParticles();
	for (Particle particle : otherParticles) {
		m_particles.push_back(new Particle(particle));
	}
}

Scene& Scene::operator=(const Scene& other) {
	std::vector<Particle> otherParticles = other.getParticles();
	for (Particle particle : otherParticles) {
		m_particles.push_back(new Particle(particle));
	}
	return *this;
}

std::vector<Particle> Scene::getParticles() const {
	std::vector<Particle> ret;
	for (Particle* particle : m_particles) {
		ret.push_back(*particle);
	}
	return ret;
}

//std::vector<Particle> Scene::getParticlesSynchronized() {
//	m_particlesMutex.lock();
//	std::vector<Particle> ret = getParticles();
//	m_particlesMutex.unlock();
//	return ret;
//}

//TO CHECK
void Scene::setParticles(std::vector<Particle*> particles) {
	m_particles.clear();
	m_particles = particles;
}

void Scene::addParticle(Particle* particle) {
	m_particles.push_back(particle);
}

void Scene::integrateAll() {
	//m_particlesMutex.lock();
	for (Particle* particle : m_particles) {
		particle->integrate();
	}
	//m_particlesMutex.unlock();
}
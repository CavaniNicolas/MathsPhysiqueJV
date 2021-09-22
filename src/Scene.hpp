#pragma once

#include <vector>
//#include <mutex>
#include "Particle.hpp"

class Scene 
{
private:

	std::vector<Particle*> m_particles;

	//std::mutex m_particlesMutex;

public:
	//Constructors
	Scene(std::vector<Particle*> particles = {});
	Scene(const Scene& other);

	//Assignation
	Scene& operator=(const Scene& other);

	//Getters
	std::vector<Particle> getParticles() const;
	//std::vector<Particle> getParticlesSynchronized();

	//Setters
	void setParticles(std::vector<Particle*> particles);
	void addParticle(Particle* particle);

	void integrateAll();
};
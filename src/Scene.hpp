#pragma once

#include <vector>
#include "Particle.hpp"

class Scene 
{
private:

	std::vector<Particle> m_particles;

public:
	//Constructors
	Scene(std::vector<Particle> particles = {});
	Scene(Scene& other);

	//Assignation
	Scene& operator=(const Scene& other);

	//Getters
	std::vector<Particle> getParticles() const;

	//Setters
	void setParticles(std::vector<Particle> particles);
	void addParticle(Particle particle);

	void integrateAll();
};
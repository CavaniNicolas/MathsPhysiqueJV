#pragma once

#include "Particle.hpp"

class ParticleForceGenerator {
private:

public:
	ParticleForceGenerator() = default;
	~ParticleForceGenerator() = default;
	virtual void updateForce(Particle* particle, float duration) = 0;
};
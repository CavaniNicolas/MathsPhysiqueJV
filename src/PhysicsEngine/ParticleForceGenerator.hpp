#pragma once

#include "Particle.hpp"
#include <memory>

class ParticleForceGenerator {
private:

public:
	virtual void updateForce(std::shared_ptr<Particle> particle, float duration) = 0;
};
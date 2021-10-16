#pragma once

#include "ParticleBuoyancy.hpp"

ParticleBuoyancy::ParticleBuoyancy(float maxDepth, float volume, float waterHeight, float liquidDensity) :
	ParticleForceGenerator(),
	m_maxDepth(maxDepth),
	m_volume(volume),
	m_waterHeight(waterHeight),
	m_liquidDensity(liquidDensity)
{}

// Apply Buoyancy based on particle position
void ParticleBuoyancy::updateForce(std::shared_ptr<Particle> particle, float duration) {
	float submergedQuantity = (particle->getPosition().getX() - m_waterHeight - m_maxDepth) / 2 * m_maxDepth;
	Vector3D force = Vector3D();
	if (submergedQuantity <= 0) {
		//The particle is not submerged at all
	}
	else if (submergedQuantity < 1) {
		//The particle is partially submerged
		force.setY(submergedQuantity * m_volume * m_liquidDensity);
	}
	else {
		//The particle is totally submerged
		force.setY(m_volume * m_liquidDensity);
	}
	particle->setAcceleration(particle->getAcceleration() + force * particle->getInverseMass());
}
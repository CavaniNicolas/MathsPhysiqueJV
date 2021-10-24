#pragma once

#include "PhysicsEngine/ParticleLink.hpp"

class ParticleRod : public ParticleLink
{
  public:
	// a contact will be generated if the distance
	// between particles is not equal to the length
    float m_length;

	ParticleRod(std::shared_ptr<Particle> particleA, std::shared_ptr<Particle> particleB, float length);

	// Fill ParticleContact with information from particles and contact generator.
	// Contact is different wether the distance is shorter or greater than the length.
    unsigned int addContact(std::vector<std::shared_ptr<ParticleContact>>& contacts, unsigned int limit) const;

};
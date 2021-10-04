#pragma once

#include "ParticleForceGenerator.hpp"
#include <memory>

class ParticleForceRegistry {
private:
	struct ParticleForceEntry {
		std::shared_ptr<Particle> particle;
		std::shared_ptr<ParticleForceGenerator> forceGenerator;
	};

	using Registry = std::vector<ParticleForceEntry>;
	Registry m_registry;
public:
	//Constructors
	ParticleForceRegistry() = default;
	ParticleForceRegistry(Registry registry);
	//Destructor
	~ParticleForceRegistry();

	//Setters
	void addEntry(std::shared_ptr<Particle> particle, std::shared_ptr<ParticleForceGenerator> forceGenerator);
	void setRegistry(Registry newRegistry);

	//Getters
	Registry getRegistry();

	void updateForce(float duration);

};
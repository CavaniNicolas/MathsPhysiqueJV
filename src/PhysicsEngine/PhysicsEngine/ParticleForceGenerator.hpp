#pragma once

#include <memory>

#include "PhysicsEngine/Particle.hpp"
#include "PhysicsEngine/ParticleContact.hpp"

class ParticleForceGenerator {
public:
    virtual unsigned int updateForce(std::shared_ptr<Particle> particle,
                             float duration,
                             std::vector<std::shared_ptr<ParticleContact>>& contacts,
                             unsigned int limit) = 0;
};

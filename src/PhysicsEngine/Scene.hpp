#pragma once

#include <memory>
#include <vector>
//#include <mutex>

#include "PhysicsEngine/Projectile.hpp"
#include "PhysicsEngine/ParticleForceRegistry.hpp"

class Scene
{
  private:
    std::vector<std::shared_ptr<Particle>> m_particles;

    ParticleForceRegistry m_forcesRegistry;

  public:
    // Constructors
    Scene(std::vector<std::shared_ptr<Particle>> particles = {},
          ParticleForceRegistry forcesRegistry = ParticleForceRegistry());
    Scene(const Scene& other);

    // Assignation
    Scene& operator=(const Scene& other);

    // Getters
    std::vector<Particle> getParticles() const;
    // std::vector<Particle> getParticlesSynchronized();

    // Setters
    void setParticles(std::vector<std::shared_ptr<Particle>> particles);
    void addParticle(std::shared_ptr<Particle> particle);
    void addForce(std::shared_ptr<Particle> particle, std::shared_ptr<ParticleForceGenerator> forceGenerator);

    void integrateAll(float deltaT);
};

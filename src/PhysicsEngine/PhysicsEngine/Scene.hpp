#pragma once

#include <memory>
#include <vector>
//#include <mutex>

#include "PhysicsEngine/Projectile.hpp"
#include "PhysicsEngine/ParticleForceRegistry.hpp"
#include "PhysicsEngine/ParticleContactResolver.hpp"
#include "PhysicsEngine/ParticleContactGenerator.hpp"

class Scene
{
  private:
    std::vector<std::shared_ptr<Particle>> m_particles;

    ParticleForceRegistry m_forcesRegistry;

    std::vector<std::shared_ptr<ParticleContact>> m_contactArray;
    ParticleContactResolver m_contactResolver;
    std::vector<std::shared_ptr<ParticleContactGenerator>> m_contactGenerators;
    int m_maxContactsPerIteration;

  public:

    // Constructors
    Scene(std::vector<std::shared_ptr<Particle>> particles = {},
          ParticleForceRegistry forcesRegistry = ParticleForceRegistry(),
          std::vector<std::shared_ptr<ParticleContactGenerator>> contactGenerators = {},
          int maxContactsPerIteration = 50);
    Scene(const Scene& other);

    // Assignation
    Scene& operator=(const Scene& other);

    // Getters
    std::vector<std::shared_ptr<Particle>> getParticles() const;
    // std::vector<Particle> getParticlesSynchronized();

    // Setters
    void setParticles(std::vector<std::shared_ptr<Particle>> particles);
    void addParticle(std::shared_ptr<Particle> particle);

    //Add a force to a specific particle
    void addForce(std::shared_ptr<Particle> particle, std::shared_ptr<ParticleForceGenerator> forceGenerator);
    
    //Add a force to each particle currently in the scene
    void addForce(std::shared_ptr<ParticleForceGenerator> forceGenerator);
    void addContactGenerator(std::shared_ptr<ParticleContactGenerator> contactGenerator);

    void integrateAll(float deltaT);
};

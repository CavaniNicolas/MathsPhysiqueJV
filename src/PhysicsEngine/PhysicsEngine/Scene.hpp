#pragma once

#include <memory>
#include <vector>
//#include <mutex>

#include "PhysicsEngine/PhysicsObject.hpp"

#include "PhysicsEngine/ParticleForceRegistry.hpp"
#include "PhysicsEngine/ParticleContactResolver.hpp"
#include "PhysicsEngine/ParticleContactGenerator.hpp"

namespace engine
{

class Scene
{
  private:
    std::vector<std::shared_ptr<PhysicsObject>> m_physicsObject;

    ParticleForceRegistry m_particleForceRegistry;

    std::vector<std::shared_ptr<ParticleContact>> m_contactArray;
    ParticleContactResolver m_contactResolver;
    std::vector<std::shared_ptr<ParticleContactGenerator>> m_particleContactGenerators;
    int m_maxContactsPerIteration;

  public:
    // Constructors
    Scene(std::vector<std::shared_ptr<PhysicsObject>> particles = {},
          ParticleForceRegistry forcesRegistry = ParticleForceRegistry(),
          std::vector<std::shared_ptr<ParticleContactGenerator>> contactGenerators = {},
          int maxContactsPerIteration = 50);
    Scene(const Scene& other);

    // Assignation
    Scene& operator=(const Scene& other);

    // Getters
    std::vector<std::shared_ptr<PhysicsObject>> getParticles() const;
    // std::vector<Particle> getParticlesSynchronized();

    // Setters
    void addParticle(std::shared_ptr<Particle> particle);

    // Add a force to a specific particle
    void addParticleForce(std::shared_ptr<Particle> particle, std::shared_ptr<ParticleForceGenerator> forceGenerator);

    // Add a force to every object currently in the scene
    void addForce(std::shared_ptr<ParticleForceGenerator> forceGenerator);
    // Add a force to every object currently in the scene
    void addParticleContactGenerator(std::shared_ptr<ParticleContactGenerator> contactGenerator);

    void integrateAll(float deltaT);
};

} // namespace engine

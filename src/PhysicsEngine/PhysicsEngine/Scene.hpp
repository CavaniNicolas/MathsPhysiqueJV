#pragma once

#include <memory>
#include <vector>
//#include <mutex>

#include "PhysicsEngine/PhysicsObject.hpp"

#include "PhysicsEngine/ForceRegistry.hpp"
#include "PhysicsEngine/ParticleForceGenerator.hpp"
#include "PhysicsEngine/ParticleContactResolver.hpp"
#include "PhysicsEngine/ParticleContactGenerator.hpp"

namespace engine
{

class Scene
{
  private:
    std::vector<std::shared_ptr<PhysicsObject>> m_physicsObject;

    ForceRegistry m_forceRegistry;

    std::vector<std::shared_ptr<ParticleContact>> m_contactArray;
    ParticleContactResolver m_contactResolver;
    std::vector<std::shared_ptr<ParticleContactGenerator>> m_particleContactGenerators;
    int m_maxContactsPerIteration;

  public:
    // Constructors
    Scene(std::vector<std::shared_ptr<PhysicsObject>> particles = {},
          ForceRegistry forcesRegistry = ForceRegistry(),
          std::vector<std::shared_ptr<ParticleContactGenerator>> contactGenerators = {},
          int maxContactsPerIteration = 50);
    Scene(const Scene& other);

    // Assignation
    Scene& operator=(const Scene& other);

    // Getters
    std::vector<std::shared_ptr<PhysicsObject>> getObjects() const;
    // std::vector<Particle> getParticlesSynchronized();

    // Setters
    void addPhysicsObject(std::shared_ptr<PhysicsObject> physicsObject);

    // Add a force to a specific particle
    void addParticleForce(std::shared_ptr<Particle> particle, std::shared_ptr<ParticleForceGenerator> forceGenerator);

    // Add a force to every object currently in the scene
    void addForceToAllParticles(std::shared_ptr<ParticleForceGenerator> forceGenerator);
    // Add a force to every object currently in the scene
    void addParticleContactGenerator(std::shared_ptr<ParticleContactGenerator> contactGenerator);

    void integrateAll(float deltaT);
};

} // namespace engine

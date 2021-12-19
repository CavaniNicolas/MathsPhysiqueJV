#pragma once

#include <memory>
#include <vector>
//#include <mutex>

#include "PhysicsEngine/BVH.hpp"
#include "PhysicsEngine/PhysicsObject.hpp"

#include "PhysicsEngine/ForceRegistry.hpp"
#include "PhysicsEngine/ParticleForceGenerator.hpp"
#include "PhysicsEngine/ParticleContactResolver.hpp"
#include "PhysicsEngine/ParticleContactGenerator.hpp"
#include "PhysicsEngine/RigidBodyForceGenerator.hpp"
#include "PhysicsEngine/RigidBodyContactGenerator.hpp"
#include "PhysicsEngine/RigidBodyContactResolver.hpp"

namespace engine
{

class Scene
{
  private:
    std::vector<std::shared_ptr<PhysicsObject>> m_physicsObject;

    ForceRegistry m_forceRegistry;

    std::vector<std::shared_ptr<ParticleContact>> m_contactArray;
    RigidBodyCollisionData m_rigidBodyCollisionData;

    ParticleContactResolver m_contactResolver;
    std::vector<std::shared_ptr<ParticleContactGenerator>> m_particleContactGenerators;
    int m_maxContactsPerIteration;

    RigidBodyContactGenerator m_rigidBodyContactGenerator;
    RigidBodyContactResolver m_rigidBodyContactResolver;
    std::vector<std::shared_ptr<Primitive>> m_primitives;

    std::shared_ptr<BVH> m_bvh;

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
    std::vector<std::shared_ptr<Primitive>> getPrimitives() const;
    // std::vector<Particle> getParticlesSynchronized();

    // Setters
    void addPhysicsObject(std::shared_ptr<PhysicsObject> physicsObject);

    // Add a force to a specific particle
    void addParticleForce(std::shared_ptr<Particle> particle, std::shared_ptr<ParticleForceGenerator> forceGenerator);
    // Add a force to every particle currently in the scene
    void addForceToAllParticles(std::shared_ptr<ParticleForceGenerator> forceGenerator);

    // Add a force to every object currently in the scene
    void addParticleContactGenerator(std::shared_ptr<ParticleContactGenerator> contactGenerator);

    // Add a force to a specific rigidbody
    void addRigidBodyForce(std::shared_ptr<RigidBody> rigidbody,
                           std::shared_ptr<RigidBodyForceGenerator> forceGenerator);
    // Add a force to every rigidbody currently in the
    void addForceToAllRigidBodies(std::shared_ptr<RigidBodyForceGenerator> forceGenerator);

    void addPrimitives(std::vector<std::shared_ptr<Primitive>> primitives);

    void buildPrimitivesFromRigidBodies();

    bool integrateAll(float deltaT);
};

} // namespace engine

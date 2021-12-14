
#include "PhysicsEngine/Scene.hpp"

namespace engine
{
Scene::Scene(std::vector<std::shared_ptr<PhysicsObject>> objects,
             ForceRegistry forcesRegistry,
             std::vector<std::shared_ptr<ParticleContactGenerator>> particleContactGenerators,
             int maxContactsPerIteration):
  m_forceRegistry(forcesRegistry),
  m_physicsObject(objects),
  m_particleContactGenerators(particleContactGenerators),
  m_maxContactsPerIteration(maxContactsPerIteration)
{
    m_contactResolver = ParticleContactResolver();
    m_contactArray = {};
}

Scene::Scene(const Scene& other)
{
    m_physicsObject = other.m_physicsObject;
    m_forceRegistry = other.m_forceRegistry;
    m_particleContactGenerators = other.m_particleContactGenerators;
    m_maxContactsPerIteration = other.m_maxContactsPerIteration;
    m_contactResolver = ParticleContactResolver();
    m_contactArray = {};
}

Scene& Scene::operator=(const Scene& other)
{
    m_physicsObject = other.m_physicsObject;
    m_forceRegistry = other.m_forceRegistry;
    m_particleContactGenerators = other.m_particleContactGenerators;
    m_maxContactsPerIteration = other.m_maxContactsPerIteration;
    return *this;
}

std::vector<std::shared_ptr<PhysicsObject>> Scene::getObjects() const
{
    return m_physicsObject;
}

// std::vector<Particle> Scene::getParticlesSynchronized() {
//	m_particlesMutex.lock();
//	std::vector<Particle> ret = getParticles();
//	m_particlesMutex.unlock();
//	return ret;
// }

void Scene::addPhysicsObject(std::shared_ptr<PhysicsObject> physicsObject)
{
    m_physicsObject.push_back(physicsObject);
}

void Scene::addParticleForce(std::shared_ptr<Particle> particle, std::shared_ptr<ParticleForceGenerator> forceGenerator)
{
    m_forceRegistry.addEntry(particle, forceGenerator);
}

void Scene::addForceToAllParticles(std::shared_ptr<ParticleForceGenerator> forceGenerator)
{
    for(auto& object: m_physicsObject)
    {
        if(std::shared_ptr<Particle> particle = std::dynamic_pointer_cast<Particle>(object))
        {
            m_forceRegistry.addEntry(particle, forceGenerator);
        }
    }
}

void Scene::addParticleContactGenerator(std::shared_ptr<ParticleContactGenerator> contactGenerator)
{
    m_particleContactGenerators.push_back(contactGenerator);
}

void Scene::addRigidBodyForce(std::shared_ptr<RigidBody> rigidbody,
                              std::shared_ptr<RigidBodyForceGenerator> forceGenerator)
{
    m_forceRegistry.addEntry(rigidbody, forceGenerator);
}

void Scene::addForceToAllRigidBodies(std::shared_ptr<RigidBodyForceGenerator> forceGenerator)
{
    for(auto& object: m_physicsObject)
    {
        if(std::shared_ptr<RigidBody> rigidbody = std::dynamic_pointer_cast<RigidBody>(object))
        {
            m_forceRegistry.addEntry(rigidbody, forceGenerator);
        }
    }
}

void Scene::addPrimitive(std::shared_ptr<Primitive> primitive)
{
    m_primitives.push_back(primitive);
}

void Scene::integrateAll(float deltaT)
{
    // We move the particles
    for(auto& object: m_physicsObject)
    {
        if(auto const& particle = std::dynamic_pointer_cast<Particle>(object))
            object->integratePosition(deltaT);
    }
    m_forceRegistry.updateForce(deltaT);
    for(auto& object: m_physicsObject)
    {
        object->integrateVelocity(deltaT);
    }
    for(auto& object: m_physicsObject)
    {
        if(auto const& rigidbody = std::dynamic_pointer_cast<RigidBody>(object))
            object->integratePosition(deltaT);
    }

    // We check for contacts
    unsigned int contacts = m_maxContactsPerIteration;
    for(auto& contactGenerator: m_particleContactGenerators)
    {
        contacts -= contactGenerator->addContact(m_contactArray, contacts);
    }
    // We resolve the found contacts
    m_contactResolver.resolveContacts(m_contactArray);
    // We processed every contact, we can now clear the contact
    // array to fill it once again during the next iteration
    m_contactArray.clear();

    m_bvh = std::make_shared<BVH>(m_primitives);
    // Resolve the possible contacts
    auto possibleContacts = m_bvh->getPossibleCollisions();
    for(auto& possibleContact: possibleContacts)
    {
        // m_rigidBodyContactGenerator.generateContact(possibleContact.first, possibleContact.second,
        // m_rigidBodyCollisionData);
    }
}

} // namespace engine

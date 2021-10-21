
#include "API/ParticleMeshRegistry.hpp"

ParticleMeshRegistry& ParticleMeshRegistry::get()
{
    // static means it will only be alocated once the first time get() is called
    static ParticleMeshRegistry instance;
    return instance;
}

void ParticleMeshRegistry::addEntryI(std::shared_ptr<Particle> particle, std::shared_ptr<RenderedMesh> renderedMesh)
{
    m_registry.push_back({particle, renderedMesh});
}

void ParticleMeshRegistry::updateMeshPositionI()
{
    for(auto const& entry: m_registry)
    {
        // creates a shared_ptr that manages the referenced object by the weak_ptr
        std::shared_ptr<RenderedMesh> renderedMesh = entry.renderedMesh.lock();
        std::shared_ptr<Particle> particle = entry.particle.lock();

        // get the actual particle position to set it to the renderedMesh
        renderedMesh->setPosition(
          {particle->getPosition().getX(), particle->getPosition().getY(), particle->getPosition().getZ()});

        renderedMesh->updateModelMatrix();
    }
}

void ParticleMeshRegistry::drawAllParticlesI(Renderer& renderer, Shader& shader, Camera& camera) const
{
    for(auto const& entry: m_registry)
    {
        // creates a shared_ptr that manages the referenced object by the weak_ptr
        std::shared_ptr<RenderedMesh> renderedMesh = entry.renderedMesh.lock();

        renderer.draw(shader, camera, *renderedMesh);
    }
}

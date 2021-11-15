#pragma once

#include "PhysicsEngine/Particle.hpp"
#include "PhysicsEngine/ParticleContact.hpp"
#include "PhysicsEngine/ForceGenerator.hpp"

namespace engine
{
class ParticleForceGenerator : public ForceGenerator
{
  protected:
    std::shared_ptr<Particle> checkParticle(std::shared_ptr<PhysicsObject> object)
    {
        if(std::shared_ptr<Particle> particle = std::dynamic_pointer_cast<Particle>(object))
        {
            return particle;
        }
        else
        {
            std::cerr << "Tried to apply a ParticleForce to a non particle object." << std::endl;
            exit(EXIT_FAILURE);
        }
    }

  public:
    // We will check if the object is a particle before really applying the force
    virtual void updateForce(std::shared_ptr<PhysicsObject> object, float duration) = 0;
};

} // namespace engine

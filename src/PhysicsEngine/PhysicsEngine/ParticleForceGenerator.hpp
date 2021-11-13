#pragma once

#include "PhysicsEngine/Particle.hpp"
#include "PhysicsEngine/ParticleContact.hpp"
#include "PhysicsEngine/ForceGenerator.hpp"

namespace engine
{
class ParticleForceGenerator : public ForceGenerator
{
  public:
    //We will check if the object is a particle before really applying the force
    virtual void updateForce(std::shared_ptr<PhysicsObject> object, float duration) = 0;
};

} // namespace engine

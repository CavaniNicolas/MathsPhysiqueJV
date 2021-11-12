#pragma once

#include "PhysicsEngine/PhysicsObject.hpp"
#include <memory>

namespace engine
{
class ForceGenerator
{
  public:
    virtual void updateForce(std::shared_ptr<PhysicsObject> object, float duration) = 0;
};
}
#pragma once

#include "ParticleContact.hpp"

class ParticleContactResolver
{
  public:
    // take an array of contact,
    // Iterate on each contact according to their separatingVelocity
    // Stop when all contacts are solved or when max iteration is reached
    void resolveContacts(std::vector<std::shared_ptr<ParticleContact>>& contactArray);
};
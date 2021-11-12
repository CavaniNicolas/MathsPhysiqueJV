#pragma once

#include "ParticleContact.hpp"

namespace engine
{

class ParticleContactGenerator
{
  public:
    // Take a pointer to an array of contact and the number of contact left to be generated
    virtual unsigned int addContact(std::vector<std::shared_ptr<ParticleContact>>& contacts,
                                    unsigned int limit) = 0;
};

} // namespace engine

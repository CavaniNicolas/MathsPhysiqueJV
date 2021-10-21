#pragma once

#include "ParticleContact.hpp"

class ParticleContactGenerator
{
  public:
	// Take a pointer to an array of contact and the number of contact left to be generated
    virtual unsigned int addContact(std::shared_ptr<std::vector<std::shared_ptr<ParticleContact>>> contacts,
                                    unsigned int limit) const = 0;
};
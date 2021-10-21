#pragma once

#include "ParticleContact.hpp"

class ParticleContactResolver
{
  protected:

	// number of allowed iteration
    unsigned int m_iteration;

  public:

	ParticleContactResolver(unsigned int iteration);

	// take an array of contact,
	// Iterate on each contact according to their separatingVelocity
	// Stop when all contacts are solved or when max iteration is reached
    void resolveContacts(std::shared_ptr<std::vector<std::shared_ptr<ParticleContact>>> contactArray,
                         unsigned int numContact,
                         float duration);
};
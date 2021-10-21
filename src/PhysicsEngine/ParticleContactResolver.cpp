#include <queue>

#include "PhysicsEngine/ParticleContactResolver.hpp"

ParticleContactResolver::ParticleContactResolver(unsigned int iteration) : m_iteration(iteration) {}

// take an array of contact,
// Iterate on each contact according to their separatingVelocity
// Stop when all contacts are solved or when max iteration is reached
void ParticleContactResolver::resolveContacts(
                     std::shared_ptr<std::vector<std::shared_ptr<ParticleContact>>> contactArray,
                     unsigned int numContact,
                     float duration)
{
    std::priority_queue<std::shared_ptr<ParticleContact>, std::vector<std::shared_ptr<ParticleContact>>, ParticleContact::HighestSeparatingVelocity> queue(contactArray->begin(), contactArray->end());

    int iterationNb = 0;

    while (!queue.empty() && iterationNb < m_iteration) {
        std::shared_ptr<ParticleContact> currentContact = queue.top();
        currentContact->resolve(duration);
        queue.pop();
        iterationNb++;
    }
}
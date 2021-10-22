#include <queue>

#include "PhysicsEngine/ParticleContactResolver.hpp"

// take an array of contact,
// Iterate on each contact according to their separatingVelocity
// Stop when all contacts are solved or when max iteration is reached
void ParticleContactResolver::resolveContacts(std::vector<std::shared_ptr<ParticleContact>>& contactArray)
{
    unsigned int maxIteration = 2 * contactArray.size();

    std::priority_queue<std::shared_ptr<ParticleContact>, std::vector<std::shared_ptr<ParticleContact>>, ParticleContact::HighestSeparatingVelocity> queue(contactArray.begin(), contactArray.end());

    unsigned int iterationNb = 0;

    while(!queue.empty() && iterationNb < maxIteration)
    {
        std::shared_ptr<ParticleContact> currentContact = queue.top();
        currentContact->resolve();
        queue.pop();
        iterationNb++;
    }
}
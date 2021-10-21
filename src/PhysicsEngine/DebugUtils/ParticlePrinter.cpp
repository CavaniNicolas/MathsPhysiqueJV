
#include <iostream>

#include "PhysicsEngine/DebugUtils/ParticlePrinter.hpp"

void ParticlePrinter::debugPrintI()
{
    // Simple timer for the Particle printing
    auto currPrintTime = std::chrono::high_resolution_clock::now();
    auto duration = currPrintTime - m_prevPrintTime;
    auto durationCastS = std::chrono::duration_cast<std::chrono::seconds>(duration);

    // TODO : replace 2.0f by m_printFrequency but m_printFrequency doesnt get initialized properly in constructor :'(
    if(durationCastS.count() >= 2.0f)
    {
        if(m_particle != nullptr)
        {
            std::cout << *m_particle << std::endl;
        }
        else
        {
            std::cerr << "Debug Warning : No particles were set to debug print" << std::endl;
        }
        m_prevPrintTime = currPrintTime;
    }
}

void ParticlePrinter::setParticleI(std::shared_ptr<Particle> particle)
{
    m_particle = particle;
}

#pragma once

#include <chrono>

#include "PhysicsEngine/Particle.hpp"

class ParticlePrinter
{
  public:
    ParticlePrinter(const ParticlePrinter&) = delete;
    ParticlePrinter& operator=(const ParticlePrinter&) = delete;

    static ParticlePrinter& get()
    {
        // static means it will only be alocated once the first time get() is called
        static ParticlePrinter instance;
        return instance;
    }

    static void debugPrint()
    {
        get().debugPrintI();
    }

    static void setParticle(std::shared_ptr<Particle> particle)
    {
        get().setParticleI(particle);
    }

  private:
    std::shared_ptr<Particle> m_particle;

    // time of the last particle printing
    std::chrono::time_point<std::chrono::steady_clock, std::chrono::duration<long long, std::ratio<1, 1000000000>>>
      m_prevPrintTime;

    // print particle every printFrequency seconds
    float m_printFrequency;

    void debugPrintI();
    void setParticleI(std::shared_ptr<Particle> particle);

    ParticlePrinter(): m_prevPrintTime(std::chrono::high_resolution_clock::now()), m_printFrequency(2.0f) {}
};

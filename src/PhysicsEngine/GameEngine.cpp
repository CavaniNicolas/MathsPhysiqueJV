
#include <chrono>
#include <ratio>
#include <thread>

#include <iostream>

#include "PhysicsEngine/GameEngine.hpp"

GameEngine::GameEngine(Scene scene, int desiredFrameRate):
  m_scene(scene), m_desiredFrameRate(desiredFrameRate), m_running(false), m_stop(false)
{
    m_gameLoopThread = std::thread([this] { gameLoop(); });
}

GameEngine::GameEngine(const GameEngine& other): GameEngine(other.m_scene, other.m_desiredFrameRate) {}

GameEngine::GameEngine(): GameEngine(Scene(), 60)
{
    m_gameLoopThread = std::thread([this] { gameLoop(); });
}

GameEngine::~GameEngine()
{
    stop();
    m_gameLoopThread.join();
}

// std::vector<Particle> GameEngine::getParticlesSynchronized() {
//	return m_scene.getParticlesSynchronized();
// }

std::vector<Particle> GameEngine::getParticles() const
{
    return m_scene.getParticles();
}

void GameEngine::gameLoop()
{
    // timeBetweenFrames in MICROSECONDS
    float timeBetweenFrames(static_cast<int>(1000000 / (static_cast<float>(m_desiredFrameRate))));

    auto lastIntegrationTime = std::chrono::high_resolution_clock::now();
    //    std::cout << "timeBetweenFrames : " << timeBetweenFrames << " us" << std::endl;
    //    std::cout << "timeBetweenFrames : " << timeBetweenFrames / 1000000 << " s" << std::endl;

    // Variable to help with the debug print
    auto lastDebugTime = std::chrono::high_resolution_clock::now();

    while(!m_stop)
    {
        if(m_running)
        {
            // determine delta Time
            auto deltaT = std::chrono::high_resolution_clock::now() - lastIntegrationTime;

            // cast delta Time into MICROSECONDS
            auto deltaTCastUS = std::chrono::duration_cast<std::chrono::microseconds>(deltaT);
            // Integrate all particles, delta time given is in SECONDS
            m_scene.integrateAll(float(deltaTCastUS.count() / 1000000.0f));

            // reset lastIntegrationTime
            lastIntegrationTime = std::chrono::high_resolution_clock::now();

            // without sleep_for... particle moves VERY slowly !!
            // my guess is : we need to wait so it doesnt integrate too much with deltaT = 0 but im not convinced
            using namespace std::literals::chrono_literals;
            std::this_thread::sleep_for(1us);

            //            // Print Debug info every seconds
            //            auto deltaTDebug = std::chrono::high_resolution_clock::now() - lastDebugTime;
            //            auto deltaTDebugCastUS = std::chrono::duration_cast<std::chrono::microseconds>(deltaTDebug);
            //            if(deltaTDebugCastUS.count() > 1000000)
            //            {
            //                std::cout << "deltaT: " << deltaTCastUS.count() << " us" << std::endl
            //                          << "deltaT: " << float(deltaTCastUS.count() / 1000000.0f) << " s" << std::endl
            //                          << std::endl;
            //                lastDebugTime = std::chrono::high_resolution_clock::now();
            //            }

            // if integration takes too long, print warning
            if(deltaTCastUS.count() > timeBetweenFrames)
            {
                std::cerr << "WARNING : too many particles to respect the desired frame rate" << std::endl;
            }
        }
        else
        {
            lastIntegrationTime = std::chrono::high_resolution_clock::now();
        }
    }
}

void GameEngine::run()
{
    m_running = true;
}

void GameEngine::pause()
{
    m_running = false;
}

void GameEngine::stop()
{
    m_stop = true;
}

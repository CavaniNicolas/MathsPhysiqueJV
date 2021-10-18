
#include <chrono>
//#include <ratio>
//#include <thread>

#include "GameEngine.hpp"

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

#include <iostream>

void GameEngine::gameLoop()
{
    std::chrono::microseconds timeBetweenFrames(static_cast<int>(1000000 / (static_cast<float>(m_desiredFrameRate))));

    // make this a member attribute
    auto desiredEndTime = std::chrono::high_resolution_clock::now() + timeBetweenFrames;

    while(!m_stop)
    {
        if(m_running)
        {
            m_scene.integrateAll();
            // std::cout << m_scene.getParticles()[0] << std::endl;

            const auto endTime = std::chrono::high_resolution_clock::now();
            if(endTime < desiredEndTime)
            {
                auto microSecToWait = std::chrono::duration_cast<std::chrono::microseconds>(desiredEndTime - endTime);
                std::cout << microSecToWait.count() << std::endl;
                std::this_thread::sleep_for(microSecToWait);
                desiredEndTime += timeBetweenFrames;
            }
            else
            {
                std::cerr << "WARNING : too many particles to respect the desired frame rate ("
                          << std::chrono::duration_cast<std::chrono::microseconds>(endTime - desiredEndTime).count()
                          << " us late)" << std::endl;
                desiredEndTime = endTime + timeBetweenFrames;
            }
        }
        else
        {
            // have this somewhere else (when unpausing for example)
            desiredEndTime = std::chrono::high_resolution_clock::now() + timeBetweenFrames;
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

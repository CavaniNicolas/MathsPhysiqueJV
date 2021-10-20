
#include <chrono>
//#include <ratio>
//#include <thread>

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

std::vector<std::shared_ptr<Particle>> GameEngine::getParticles() const
{
    return m_scene.getParticles();
}

//#include <iostream>
// void GameEngine::gameLoop()
//{
//    std::chrono::microseconds timeBetweenFrames(static_cast<int>(1000000 / (static_cast<float>(m_desiredFrameRate))));

//    // make this a member attribute
//    auto lastIntegrationTime = std::chrono::high_resolution_clock::now();

//    // Calculate deltaT
//    while(!m_stop)
//    {
//        if(m_running)
//        {
//            auto deltaT = std::chrono::high_resolution_clock::now() - lastIntegrationTime;
//            float lala = (float)(deltaT.count() / 1000000);
//            m_scene.integrateAll(lala);
//            //            std::cout << m_scene.getParticles()[0] << std::endl;

//            if(deltaT > timeBetweenFrames)
//            {
//                std::cerr << "WARNING : too many particles to respect the desired frame rate" << std::endl;
//            }

//            lastIntegrationTime = std::chrono::high_resolution_clock::now();
//        }
//        else
//        {
//            lastIntegrationTime = std::chrono::high_resolution_clock::now();
//        }
//    }
//}

void GameEngine::gameLoop()
{
    float timeBetweenFrames = 1 / (static_cast<float>(m_desiredFrameRate));

    float lastIntegrationTime = static_cast<float>(clock()) / CLOCKS_PER_SEC;

    // Calculate deltaT
    while(!m_stop)
    {
        if(m_running)
        {
            float deltaT = static_cast<float>(clock()) / CLOCKS_PER_SEC - lastIntegrationTime;
            m_scene.integrateAll(deltaT);
            //            std::cout << m_scene.getParticles()[0] << std::endl;

            if(deltaT > timeBetweenFrames)
            {
                std::cerr << "WARNING : too many particles to respect the desired frame rate" << std::endl;
            }

            lastIntegrationTime = static_cast<float>(clock()) / CLOCKS_PER_SEC;
        }
        else
        {
            lastIntegrationTime = static_cast<float>(clock()) / CLOCKS_PER_SEC;
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

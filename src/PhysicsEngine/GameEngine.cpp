
#include <Windows.h>

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

void GameEngine::gameLoop()
{
    float timeBetweenFrames = 1 / (static_cast<float>(m_desiredFrameRate));

    float desiredEndTime = static_cast<float>(clock()) / CLOCKS_PER_SEC + timeBetweenFrames;

    while(!m_stop)
    {
        if(m_running)
        {
            m_scene.integrateAll();
            // std::cout << m_scene.getParticles()[0] << std::endl;

            float endTime = static_cast<float>(clock()) / CLOCKS_PER_SEC;
            if(endTime < desiredEndTime)
            {
                float milliSecToWait = (desiredEndTime - endTime) * 1000;
                Sleep(milliSecToWait);
                desiredEndTime += timeBetweenFrames;
            }
            else
            {
                std::cerr << "WARNING : too many particles to respect the desired frame rate ("
                          << endTime - desiredEndTime << "s late)" << std::endl;
                desiredEndTime = endTime + timeBetweenFrames;
            }
        }
        else
        {
            desiredEndTime = static_cast<float>(clock()) / CLOCKS_PER_SEC + timeBetweenFrames;
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

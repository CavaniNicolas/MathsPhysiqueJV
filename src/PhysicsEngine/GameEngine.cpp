#include <Windows.h>
#include "GameEngine.hpp"

GameEngine::GameEngine(Scene scene, int desiredFrameRate):
    m_scene(scene),
    m_desiredFrameRate(desiredFrameRate),
    m_running(false),
    m_stop(false)
{
	m_gameLoopThread = std::thread([this] { gameLoop(); });
}

GameEngine::GameEngine(const GameEngine& other):
	GameEngine(other.m_scene, other.m_desiredFrameRate)
{}

GameEngine::GameEngine():
    GameEngine(Scene(), 60)
{
	m_gameLoopThread = std::thread([this] { gameLoop(); });
}

GameEngine::~GameEngine()
{
	stop();
	m_gameLoopThread.join();
}

//std::vector<Particle> GameEngine::getParticlesSynchronized() {
//	return m_scene.getParticlesSynchronized();
//}

std::vector<Particle> GameEngine::getParticles() const {
	return m_scene.getParticles();
}

void GameEngine::gameLoop() {

	float timeBetweenFrames = 1 / (static_cast<float>(m_desiredFrameRate));

	float lastIntegrationTime = static_cast<float>(clock()) / CLOCKS_PER_SEC;

	//Calculate deltaT
	while (!m_stop) {
		if (m_running) {
			float deltaT = static_cast<float>(clock()) / CLOCKS_PER_SEC - lastIntegrationTime;
			m_scene.integrateAll(deltaT);
			//std::cout << m_scene.getParticles()[0] << std::endl;

			if (deltaT > timeBetweenFrames) {
				std::cerr << "WARNING : too many particles to respect the desired frame rate" << std::endl;
			}

			lastIntegrationTime = static_cast<float>(clock()) / CLOCKS_PER_SEC;
		}
	}
}

void GameEngine::run() {
	m_running = true;
}

void GameEngine::pause() {
	m_running = false;
}

void GameEngine::stop() {
	m_stop = true;
}

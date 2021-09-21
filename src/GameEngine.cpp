#include <Windows.h>
#include "GameEngine.hpp"

GameEngine::GameEngine(Scene scene, int desiredFrameRate) {
	m_scene = scene;
	m_desiredFrameRate = desiredFrameRate;
	m_running = false;
	m_stop = false;

	m_gameLoopThread = std::thread([this] { gameLoop(); });
}

GameEngine::GameEngine(GameEngine& other) :
	GameEngine(other.m_scene, other.m_desiredFrameRate)
{ }

GameEngine::GameEngine() {
	m_scene = Scene();
	m_desiredFrameRate = 60;
	m_running = false;
	m_stop = false;

	m_gameLoopThread = std::thread([this] { gameLoop(); });
}

GameEngine::~GameEngine() {
	stop();
	m_gameLoopThread.join();
}

std::vector<Particle*> GameEngine::getParticles() {
	m_mutexParticles.lock();
	std::vector<Particle*> tempParticles = m_scene.getParticles();
	m_mutexParticles.unlock();
	return tempParticles;
}

void GameEngine::gameLoop() {

	std::cout << "Entered gameLoop" << std::endl;

	float timeBetweenFrames = 1 / ((float)m_desiredFrameRate);

	float desiredEndTime = (float)(clock()) / CLOCKS_PER_SEC + timeBetweenFrames;

	while (1) {
		if (!m_stop) {
			if (m_running) {
				m_mutexParticles.lock();
				m_scene.integrateAll();
				std::cout << *m_scene.getParticles()[0] << std::endl;
				m_mutexParticles.unlock();

				float endTime = (float)(clock()) / CLOCKS_PER_SEC;
				if (endTime < desiredEndTime) {
					float milliSecToWait = (desiredEndTime - endTime) * 1000;
					Sleep(milliSecToWait);
					desiredEndTime = (float)(clock()) / CLOCKS_PER_SEC + timeBetweenFrames;
				}
				else {
					std::cerr << "WARNING : too many particles to respect the desired frame rate" << std::endl;
					desiredEndTime = endTime + timeBetweenFrames;
				}
			}
		}
		else {
			break;
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
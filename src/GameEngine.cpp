#include "GameEngine.hpp"

GameEngine::GameEngine(Scene scene) {
	m_scene = scene;

	m_thread = std::thread();
}

GameEngine::GameEngine() {

}

std::vector<Particle> GameEngine::getParticles() const {
	//CHECK MUTEX
	return m_scene.getParticles();
}

void GameEngine::gameLoop() {

	while (m_running) {
		//do stuff
	}
}

void GameEngine::run() {
	m_running = true;
}

void GameEngine::stop() {
	m_running = false;
}
#pragma once

#include <thread>
#include "Scene.hpp"

class GameEngine
{
private:

	Scene m_scene;

	bool m_running;
	std::thread m_thread;

public:

	GameEngine(Scene scene);
	GameEngine();

	std::vector<Particle> getParticles() const;

	void gameLoop();

	void run();
	void stop();
};
#pragma once

#include <thread>
#include <mutex>
#include "Scene.hpp"

class GameEngine
{
private:

	Scene m_scene;

	bool m_running;
	bool m_stop;
	std::thread m_gameLoopThread;
	std::mutex m_mutexParticles;

	int m_desiredFrameRate;

public:

	GameEngine(Scene scene, int desiredFrameRate = 60);
	GameEngine(GameEngine& other);
	GameEngine();
	~GameEngine();

	std::vector<Particle*> getParticles();

	void gameLoop();

	void run();
	void pause();
	void stop();
};
#pragma once

#include <thread>

#include "PhysicsEngine/Scene.hpp"

class GameEngine
{
  private:
    Scene m_scene;

    // true if we calculate the particles' information
    bool m_running;
    // true if we want to stop the engine
    bool m_stop;
    std::thread m_gameLoopThread;

    int m_desiredFrameRate;

  public:
    GameEngine(Scene scene, int desiredFrameRate = 60);
    GameEngine(const GameEngine& other);
    GameEngine();
    ~GameEngine();

    // std::vector<Particle> getParticlesSynchronized();

    std::vector<Particle> getParticles() const;

    void gameLoop();

    void run();
    void pause();
    void stop();
};

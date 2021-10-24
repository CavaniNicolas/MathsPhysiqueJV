#pragma once

#include <thread>

#include "PhysicsEngine/Scene.hpp"

class GameEngine
{
  private:
    std::shared_ptr<Scene> m_scene;

    // true if we calculate the particles' information
    bool m_running;
    // true if we want to stop the engine
    bool m_stop;
    std::thread m_gameLoopThread;

    int m_desiredFrameRate;

  public:
    GameEngine(std::shared_ptr<Scene> scene, int desiredFrameRate = 60);
    GameEngine(const GameEngine& other);
    GameEngine();
    ~GameEngine();

    // std::vector<Particle> getParticlesSynchronized();

    std::vector<std::shared_ptr<Particle>> getParticles() const;

    void gameLoop();

    void run();
    void pause();
    void stop();

    std::shared_ptr<Scene> getScene() const
    {
        return m_scene;
    }
};

#pragma once

#include <PhysicsEngine/GameEngine.hpp>

#include "Camera.hpp"
#include "Window.hpp"

class UserInterface
{
  public:
    UserInterface(Window window);

    void start() const;
    void terminate() const;
    void render(GameEngine& gameEngine, Camera& camera) const;
};

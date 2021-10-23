#pragma once

#include <PhysicsEngine/GameEngine.hpp>

#include <Render/Camera.hpp>
#include <Render/Window.hpp>

class UserInterface
{
  public:
    UserInterface(render::Window window);

    void start() const;
    void terminate() const;
    void render(GameEngine& gameEngine, render::Camera& camera) const;
};

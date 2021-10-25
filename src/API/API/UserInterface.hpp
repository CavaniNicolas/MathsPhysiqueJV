#pragma once

#include <PhysicsEngine/GameEngine.hpp>

#include <Render/Camera.hpp>
#include <Render/Window.hpp>

namespace api
{

class UserInterface
{
  public:
    UserInterface(render::Window window);

    void start() const;
    void terminate() const;
    void render(engine::GameEngine& gameEngine, render::Camera& camera) const;
};

} // namespace api

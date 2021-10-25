#pragma once

#include <API/ScenesAPI.hpp>
#include <PhysicsEngine/GameEngine.hpp>

#include <Render/Camera.hpp>
#include <Render/Window.hpp>

class UserInterface
{
  public:
    UserInterface(render::Window window);

    void start() const;
    void terminate() const;
    void render(engine::GameEngine& gameEngine, api::ScenesAPI& scenesAPI, render::Camera& camera) const;
    void showProjectileCreation(api::ScenesAPI& scenesAPI) const;
    void HelpMarker(const char* desc) const;
};

#pragma once

#include <API/ScenesAPI.hpp>
#include <PhysicsEngine/GameEngine.hpp>

#include <Render/Camera.hpp>
#include <Render/Window.hpp>

class UserInterface
{
  private:
    float generateRandomFloat(float minVal, float maxVal) const;

    float m_xMovement;
    float m_yMovement;
    float m_zMovement;

  public:
    UserInterface(render::Window window);

    void start() const;
    void terminate() const;
    void render(GameEngine& gameEngine, api::ScenesAPI& scenesAPI, render::Camera& camera);
    void showProjectileCreation(api::ScenesAPI& scenesAPI) const;
    void moveBlob(api::ScenesAPI& scenesAPI);
    void HelpMarker(const char* desc) const;
};

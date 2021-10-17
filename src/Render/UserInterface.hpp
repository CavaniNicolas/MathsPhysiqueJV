#pragma once

// Include imgui
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

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

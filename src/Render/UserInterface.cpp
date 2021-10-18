
// Include imgui
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include "Render/UserInterface.hpp"

UserInterface::UserInterface(Window window)
{
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";

    // Setup ImGui binding
    ImGui::CreateContext();

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    // ImGui::StyleColorsClassic();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window.getWindow(), true);
    ImGui_ImplOpenGL3_Init(glsl_version);
}

void UserInterface::start() const
{
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void UserInterface::terminate() const
{
    // Cleanup imgui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void UserInterface::render(GameEngine& gameEngine, Camera& camera) const
{
    float cameraAngle = camera.getFOVdeg();

    // Show a simple window that we create ourselves. We use a Begin/End pair
    // to create a named window.
    ImGui::Begin("Hello, world!"); // Create a window called "Hello,
                                   // world!" and append into it.
    ImGui::SliderFloat("cameraAngle",
                       &cameraAngle,
                       0.0f,
                       90.0f); // Edit translation.x using a slider from -100.0f to 100.0f
    if(ImGui::Button("Run Simulation"))
    {
        gameEngine.run();
    }
    if(ImGui::Button("Pause Simulation"))
    {
        gameEngine.pause();
    }

    ImGui::Text(
      "Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();

    camera.setFOVdeg(cameraAngle);

    // Rendering imgui
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}


// Include imgui
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include "PhysicsEngine/RigidBodySpring.hpp"

#include "mainApp3/UserInterface.hpp"

float UserInterface::generateRandomFloat(float minVal, float maxVal) const
{
    return minVal + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (maxVal - minVal)));
}

UserInterface::UserInterface(render::Window window): m_xMovement(0), m_yMovement(0), m_zMovement(0)
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

void UserInterface::showSpringCreation(api::ScenesAPI& scenesAPI) const
{
    if(ImGui::TreeNode("Spring creation"))
    {
        static float springConstant = .2f;
        static float restLength = 15;

        // Table with the spring constant
        if(ImGui::BeginTable("SpringConstant", 1))
        {
            ImGui::TableNextRow();

            ImGui::TableSetColumnIndex(0);
            ImGui::Text("Spring constant");

            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::InputFloat("Constant", &springConstant);
            ImGui::SameLine();
            HelpMarker("Here you can determine how strong the springs linking the particles will be.");

            ImGui::EndTable();
        }

        // Table with the rest length
        if(ImGui::BeginTable("RestLength", 1))
        {
            ImGui::TableNextRow();

            ImGui::TableSetColumnIndex(0);
            ImGui::Text("Rest length");

            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::InputFloat("Length", &restLength);
            ImGui::SameLine();
            HelpMarker("Here you can determine the springs' rest length.\n"
                       "If the spring's length is below this length, the spring will push the\n"
                       "particles appart, and if the spring's length if above this length, the\n"
                       "spring will push them towards each other.");

            ImGui::EndTable();
        }

        // Button to create a projectile with the selected position and direction
        if(ImGui::Button("Create spring"))
        {
            auto& rigidBody1 = std::dynamic_pointer_cast<engine::RigidBody>(scenesAPI.getSceneEngine()->getObjects()[0]);
            auto& rigidBody2 = std::dynamic_pointer_cast<engine::RigidBody>(scenesAPI.getSceneEngine()->getObjects()[1]);

            std::shared_ptr<engine::RigidBodySpring> spring = std::make_shared<engine::RigidBodySpring>(
              engine::Vector3D(1, 1, 0), rigidBody2, engine::Vector3D(1, 1, 0), springConstant, restLength);

            scenesAPI.getSceneEngine()->addRigidBodyForce(rigidBody1, spring);
        }
        ImGui::TreePop();
    }
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

// Helper to display a little (?) mark which shows a tooltip when hovered.
void UserInterface::HelpMarker(const char* desc) const
{
    ImGui::TextDisabled("(?)");
    if(ImGui::IsItemHovered())
    {
        ImGui::BeginTooltip();
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ImGui::TextUnformatted(desc);
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
}

void UserInterface::render(engine::GameEngine& gameEngine, api::ScenesAPI& scenesAPI, render::Camera& camera)
{
    float cameraAngle = camera.getFOVdeg();

    // Use a Begin/End pair to create a named window. create a window and append into it
    ImGui::Begin("Scene Editor");

    // Edit translation.x using a slider from 0.0f to 90.0f
    ImGui::SliderFloat("cameraAngle", &cameraAngle, 0.0f, 90.0f);

    showSpringCreation(scenesAPI);

    // Buttons to run and pause the simulation
    if(ImGui::Button("Run Simulation"))
    {
        gameEngine.run();
    }
    ImGui::SameLine();
    if(ImGui::Button("Pause Simulation"))
    {
        gameEngine.pause();
    }

    // Display framerate
    ImGui::Text(
      "Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();

    // actually set what has been modified using imgui
    camera.setFOVdeg(cameraAngle);

    // Rendering imgui
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
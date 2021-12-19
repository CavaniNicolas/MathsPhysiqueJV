
// Include imgui
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include "PhysicsEngine/Plan.hpp"
#include "PhysicsEngine/RigidBodyGravity.hpp"

#include "mainApp4/UserInterface.hpp"

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

void UserInterface::showSceneParameters(api::ScenesAPI& scenesAPI) const
{
    if(ImGui::TreeNode("Parameters"))
    {
        static int speedX = 0;
        static int speedY = 10;
        static int speedZ = 30;

        static int rotationX = 0;
        static int rotationY = 0;
        static int rotationZ = 0;

        static int normalX = 0;
        static int normalY = 1;
        static int normalZ = 0;

        static float planOffset = 0;

        // Table with position input boxes
        if(ImGui::BeginTable("Speed", 3))
        {
            ImGui::TableNextRow();

            ImGui::TableSetColumnIndex(0);
            ImGui::Text("Speed");

            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::InputInt("X", &speedX);
            ImGui::TableSetColumnIndex(1);
            ImGui::InputInt("Y", &speedY);
            ImGui::TableSetColumnIndex(2);
            ImGui::InputInt("Z", &speedZ);
            ImGui::SameLine();
            HelpMarker("Choose the car's linear velocity.\n");

            ImGui::EndTable();
        }

        // Table with position input boxes
        if(ImGui::BeginTable("Rotation", 3))
        {
            ImGui::TableNextRow();

            ImGui::TableSetColumnIndex(0);
            ImGui::Text("Rotation");

            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::InputInt("X", &rotationX);
            ImGui::TableSetColumnIndex(1);
            ImGui::InputInt("Y", &rotationY);
            ImGui::TableSetColumnIndex(2);
            ImGui::InputInt("Z", &rotationZ);
            ImGui::SameLine();
            HelpMarker("Choose the car's angular velocity.\n");

            ImGui::EndTable();
        }

        // Table with position input boxes
        if(ImGui::BeginTable("Plan's normal", 3))
        {
            ImGui::TableNextRow();

            ImGui::TableSetColumnIndex(0);
            ImGui::Text("Plan's normal");

            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::InputInt("X", &normalX);
            ImGui::TableSetColumnIndex(1);
            ImGui::InputInt("Y", &normalY);
            ImGui::TableSetColumnIndex(2);
            ImGui::InputInt("Z", &normalZ);
            ImGui::SameLine();
            HelpMarker("Choose the plan's normal.\n");

            ImGui::EndTable();
        }

        if(ImGui::BeginTable("Plan's offset", 1))
        {
            ImGui::TableNextRow();

            ImGui::TableSetColumnIndex(0);
            ImGui::Text("Plan's offset");

            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::InputFloat("Offset", &planOffset);
            ImGui::SameLine();
            HelpMarker("Choose the wall's offset (its height in the normal direction).");

            ImGui::EndTable();
        }

        // Button to create a projectile with the selected position and direction
        if(ImGui::Button("Apply changes"))
        {
            std::shared_ptr<engine::RigidBody> car =
              std::dynamic_pointer_cast<engine::RigidBody>(scenesAPI.getSceneEngine()->getObjects()[0]);
            car->setVelocity(engine::Vector3D(speedX, speedY, speedZ));
            car->setRotation(engine::Vector3D(rotationX, rotationY, rotationZ));

            std::shared_ptr<engine::Plan> plan =
              std::dynamic_pointer_cast<engine::Plan>(scenesAPI.getSceneEngine()->getPrimitives()[0]);
            plan->setNormal(engine::Vector3D(normalX, normalY, normalZ));
            plan->setPlanOffset(planOffset);
        }

        // Button to create a projectile with the selected position and direction
        if(ImGui::Button("Apply gravity"))
        {
            std::shared_ptr<engine::RigidBodyGravity> gravity = std::make_shared<engine::RigidBodyGravity>();
            scenesAPI.getSceneEngine()->addForceToAllRigidBodies(gravity);
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

    showSceneParameters(scenesAPI);

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
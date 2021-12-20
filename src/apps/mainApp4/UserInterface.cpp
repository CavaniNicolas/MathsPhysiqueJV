
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
        bool gravityON = false;
        bool applyChanges = false;

        static int speedX = 0;
        static int speedY = 5;
        static int speedZ = 0;

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

        // Presets
        {
            ImGui::Text("Select a preset to set up the scene");

            if(ImGui::Button("Preset 1"))
            {
                normalX = 0;
                normalY = 1;
                normalZ = 0;
                planOffset = 0;
                speedX = 1;
                speedY = 5;
                speedZ = 1;

                rotationX = 5;
                rotationY = 5;
                rotationZ = 5;

                gravityON = true;
                applyChanges = true;
            }
            ImGui::SameLine();
            HelpMarker(
              "plan's normal : (0, 1, 0). Offset = 0. Car speed = (1, 5, 1). Car Rotation = (5, 5, 5). Gravity ON\n");

            if(ImGui::Button("Preset 2"))
            {
                normalX = 0;
                normalY = -1;
                normalZ = 0;
                planOffset = 25;
                speedX = 0;
                speedY = 30;
                speedZ = 0;

                rotationX = 5;
                rotationY = -2;
                rotationZ = 5;

                applyChanges = true;
            }
            ImGui::SameLine();
            HelpMarker("plan's normal : (0, -1, 0). Offset = 25. Car speed = (0, 30, 0). Car Rotation = (5, -2, 5).\n");

            if(ImGui::Button("Preset 3"))
            {
                normalX = -1;
                normalY = 0;
                normalZ = 0;
                planOffset = 20;
                speedX = 50;
                speedY = 5;
                speedZ = 0;

                applyChanges = true;
            }
            ImGui::SameLine();
            HelpMarker("plan's normal : (-1, 0, 0). Offset = 20. Car speed = (50, 5, 0)\n");

            if(ImGui::Button("Preset 4"))
            {
                normalX = -1;
                normalY = 0;
                normalZ = 0;
                planOffset = 40;
                speedX = 50;
                speedY = 5;
                speedZ = 0;
                rotationX = 1;
                rotationY = 1;
                rotationZ = 1;

                applyChanges = true;
            }
            ImGui::SameLine();
            HelpMarker("plan's normal : (-1, 0, 0). Offset = 40. Car speed = (50, 5, 0). Car Rotation = (1, 1, 1).\n");
        }

        // Button to create a projectile with the selected position and direction
        if(ImGui::Button("Apply changes"))
        {
            applyChanges = true;
        }

        // Button to create a projectile with the selected position and direction
        if(ImGui::Button("Apply gravity"))
        {
            gravityON = true;
        }
        ImGui::TreePop();

        if(gravityON)
        {
            std::shared_ptr<engine::RigidBodyGravity> gravity = std::make_shared<engine::RigidBodyGravity>();
            scenesAPI.getSceneEngine()->addForceToAllRigidBodies(gravity);

            gravityON = false;
        }

        if(applyChanges)
        {
            std::shared_ptr<engine::RigidBody> car =
              std::dynamic_pointer_cast<engine::RigidBody>(scenesAPI.getSceneEngine()->getObjects()[0]);
            car->setVelocity(engine::Vector3D(speedX, speedY, speedZ));
            car->setRotation(engine::Vector3D(rotationX, rotationY, rotationZ));

            std::shared_ptr<engine::Plan> plan =
              std::dynamic_pointer_cast<engine::Plan>(scenesAPI.getSceneEngine()->getPrimitives()[0]);
            plan->setNormal(engine::Vector3D(normalX, normalY, normalZ));
            plan->setPlanOffset(planOffset);

            applyChanges = false;
        }
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


// Include imgui
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include <PhysicsEngine/Projectile.hpp>
#include <PhysicsEngine/Bullet.hpp>
#include <PhysicsEngine/Fireball.hpp>
#include <PhysicsEngine/Laser.hpp>

#include "mainApp1/UserInterface.hpp"

UserInterface::UserInterface(render::Window window)
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

void UserInterface::showProjectileCreation(api::ScenesAPI& scenesAPI) const
{
    if(ImGui::TreeNode("Projectile Creation"))
    {
        static int xP = 0;
        static int yP = 0;
        static int zP = 0;

        static int xD = 0;
        static int yD = 0;
        static int zD = 0;

        // Table with position input boxes
        if(ImGui::BeginTable("Postion", 3))
        {
            ImGui::TableNextRow();

            ImGui::TableSetColumnIndex(0);
            ImGui::Text("Position");

            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::InputInt("X", &xP);
            ImGui::TableSetColumnIndex(1);
            ImGui::InputInt("Y", &yP);
            ImGui::TableSetColumnIndex(2);
            ImGui::InputInt("Z", &zP);
            ImGui::SameLine();
            HelpMarker("You can apply arithmetic operators +,*,/ on numerical values.\n"
                       "  e.g. [ 100 ], input \'*2\', result becomes [ 200 ]\n"
                       "Use +- to subtract.");

            ImGui::EndTable();
        }

        // Table with position input boxes
        if(ImGui::BeginTable("Direction", 3))
        {
            ImGui::TableNextRow();

            ImGui::TableSetColumnIndex(0);
            ImGui::Text("Direction");

            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::InputInt("X", &xD);
            ImGui::TableSetColumnIndex(1);
            ImGui::InputInt("Y", &yD);
            ImGui::TableSetColumnIndex(2);
            ImGui::InputInt("Z", &zD);
            ImGui::SameLine();
            HelpMarker("You can apply arithmetic operators +,*,/ on numerical values.\n"
                       "  e.g. [ 100 ], input \'*2\', result becomes [ 200 ]\n"
                       "Use +- to subtract.");

            ImGui::EndTable();
        }

        // Using the generic BeginCombo() API, you have full control over how to display the combo contents.
        // (your selection data could be an index, a pointer to the object, an id for the object, a flag intrusively
        // stored in the object itself, etc.)
        const char* items[] = {"Bullet", "Fireball", "Laser"};
        // Here we store our selection data as an index.
        static int item_current_idx = 0;
        // Pass in the preview value visible before opening the combo (it could be anything)
        const char* combo_preview_value = items[item_current_idx];
        if(ImGui::BeginCombo("Type", combo_preview_value, 0))
        {
            for(int n = 0; n < IM_ARRAYSIZE(items); n++)
            {
                const bool is_selected = (item_current_idx == n);
                if(ImGui::Selectable(items[n], is_selected))
                    item_current_idx = n;

                // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                if(is_selected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
        }

        // Button to create a projectile with the selected position and direction
        if(ImGui::Button("Create Projectile"))
        {
            std::shared_ptr<Projectile> projectile;

            // Create the Projectile
            if(item_current_idx == 0)
            {
                projectile = std::make_shared<Bullet>(Vector3D(xP, yP, zP), Vector3D(xD, yD, zD), 1, 1);
            }
            if(item_current_idx == 1)
            {
                projectile = std::make_shared<Fireball>(Vector3D(xP, yP, zP), Vector3D(xD, yD, zD), 1, 1);
            }
            if(item_current_idx == 2)
            {
                projectile = std::make_shared<Laser>(Vector3D(xP, yP, zP), Vector3D(xD, yD, zD), 1, 1);
            }

            scenesAPI.addParticleDefault(projectile);
        }
        ImGui::TreePop();
    }
}

void UserInterface::render(GameEngine& gameEngine, api::ScenesAPI& scenesAPI, render::Camera& camera) const
{
    float cameraAngle = camera.getFOVdeg();

    // Use a Begin/End pair to create a named window. create a window and append into it
    ImGui::Begin("Scene Editor");

    // Edit translation.x using a slider from 0.0f to 90.0f
    ImGui::SliderFloat("cameraAngle", &cameraAngle, 0.0f, 90.0f);

    showProjectileCreation(scenesAPI);

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

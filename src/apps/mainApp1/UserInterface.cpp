
// Include imgui
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include <API/ParticleMeshRegistry.hpp>

#include <PhysicsEngine/Projectile.hpp>
#include <PhysicsEngine/Bullet.hpp>
#include <PhysicsEngine/Fireball.hpp>
#include <PhysicsEngine/Laser.hpp>

#include <Render/RenderedMesh.hpp>

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
static void HelpMarker(const char* desc)
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

void showProjectileCreation(GameEngine& gameEngine)
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
            // NOT GOOD, CREATE A PROPER CLASS
            // Store mesh data in vectors for the mesh
            std::vector<render::Vertex> verts = {//              COORDINATES           /           TexCoord    //
                                                 render::Vertex{glm::vec3(-5.0f, 0.0f, 5.0f), glm::vec2(0.32f, 0.32f)},
                                                 render::Vertex{glm::vec3(5.0f, 0.0f, 5.0f), glm::vec2(0.69f, 0.32f)},
                                                 render::Vertex{glm::vec3(5.0f, 0.0f, -5.0f), glm::vec2(0.69f, 0.69f)},
                                                 render::Vertex{glm::vec3(-5.0f, 0.0f, -5.0f), glm::vec2(0.32f, 0.69f)},

                                                 render::Vertex{glm::vec3(0.0f, 8.0f, 0.0f), glm::vec2(0.5f, 0.0f)},
                                                 render::Vertex{glm::vec3(0.0f, 8.0f, 0.0f), glm::vec2(1.0f, 0.5f)},
                                                 render::Vertex{glm::vec3(0.0f, 8.0f, 0.0f), glm::vec2(0.5f, 1.0f)},
                                                 render::Vertex{glm::vec3(0.0f, 8.0f, 0.0f), glm::vec2(0.0f, 0.5f)}};
            std::vector<unsigned int> indices = {0, 1, 2, 2, 3, 0, 0, 1, 4, 1, 2, 5, 2, 3, 6, 3, 0, 7};
            render::Mesh pyramidMesh(verts, indices);

            // Create the RenderedMesh
            std::shared_ptr<render::RenderedMesh> pyramid = std::make_shared<render::RenderedMesh>(
              pyramidMesh, std::string(RESOURCE_PATH) + "textures/fire_texture_pyramid.png");

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

            gameEngine.getScene()->addParticle(projectile);
            ParticleMeshRegistry::addEntry(projectile, pyramid);
        }
        ImGui::TreePop();
    }
}

void UserInterface::render(GameEngine& gameEngine, render::Camera& camera) const
{
    float cameraAngle = camera.getFOVdeg();

    // Use a Begin/End pair to create a named window. create a window and append into it
    ImGui::Begin("Scene Editor");

    // Edit translation.x using a slider from 0.0f to 90.0f
    ImGui::SliderFloat("cameraAngle", &cameraAngle, 0.0f, 90.0f);

    showProjectileCreation(gameEngine);

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


// Include imgui
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include "PhysicsEngine/CableSpring.hpp"
#include "PhysicsEngine/WallContactGenerator.hpp"
#include "PhysicsEngine/ParticleGravity.hpp"
#include "PhysicsEngine/ParticleDrag.hpp"

#include "mainApp2/UserInterface.hpp"

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
    if(ImGui::TreeNode("Blob creation"))
    {
        static int particlesNb = 1;
        static float springConstant = 1.2;
        static float restLength = 3;
        static float elasticityLimitLength = 10;
        static float restitutionCoef = 0;
        static float k1 = 0;
        static float k2 = 0;

        // Table with the number of particles
        if(ImGui::BeginTable("ParticlesNb", 1))
        {
            ImGui::TableNextRow();

            ImGui::TableSetColumnIndex(0);
            ImGui::Text("Number of particles");

            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::InputInt("Nb", &particlesNb);
            ImGui::SameLine();
            HelpMarker("Here you can chose the number of particles that will form your blob.");

            ImGui::EndTable();
        }

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

        // Table with the rest length
        if(ImGui::BeginTable("ElasticityLimitLength", 1))
        {
            ImGui::TableNextRow();

            ImGui::TableSetColumnIndex(0);
            ImGui::Text("Elasticity limit length");

            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::InputFloat("Limit length", &elasticityLimitLength);
            ImGui::SameLine();
            HelpMarker("Here you can determine the springs' elasticity limit length.\n"
                       "If the spring's length is above this length, the spring will act as\n"
                       "a cable. This means that there will be a strong force pushing the\n"
                       "particles towards each other.");

            ImGui::EndTable();
        }

        // Table with the rest length
        if(ImGui::BeginTable("RestitutionCoef", 1))
        {
            ImGui::TableNextRow();

            ImGui::TableSetColumnIndex(0);
            ImGui::Text("Restitution coefficient");

            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::InputFloat("Coefficient", &restitutionCoef);
            ImGui::SameLine();
            HelpMarker("Here you can determine how strong the particles will be pushed\n"
                       "towards each other when the length is above the limit length.");

            ImGui::EndTable();
        }

        // Table with the drag coefficients
        if(ImGui::BeginTable("Drag coefficients", 2))
        {
            ImGui::TableNextRow();

            ImGui::TableSetColumnIndex(0);
            ImGui::Text("Drag Restitution coefficients");
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::InputFloat("k1", &k1);
            ImGui::TableSetColumnIndex(1);
            ImGui::InputFloat("k2", &k2);
            ImGui::SameLine();
            HelpMarker("Here you can determine how the particles will be "
                       "slowed down lineary (with k1) and quadratically (with k2)."
                       "You should keep the values between 0 and 1"
                       "if you want the particles to keep moving");

            ImGui::EndTable();
        }

        // Button to create a projectile with the selected position and direction
        if(ImGui::Button("Create blob"))
        {
            // The range determines how close to the first particle the other particles will be created
            float range = 1;
            // We keep a reference to the first particle to be able to move it afterwards
            std::shared_ptr<engine::Particle> firstParticle;
            std::vector<std::shared_ptr<engine::Particle>> particles;
            // We create the requested number of particles and add them to the scene
            if(particlesNb > 0)
            {
                firstParticle = std::make_shared<engine::Particle>(engine::Vector3D(0, 30, 0), engine::Vector3D());
                scenesAPI.addParticleDefault(firstParticle);
                particles.push_back(firstParticle);
            }
            for(int i = 1; i < particlesNb; i++)
            {
                std::shared_ptr<engine::Particle> currentParticle =
                  std::make_shared<engine::Particle>(engine::Vector3D(0 + generateRandomFloat(-range, range),
                                                                      30 + generateRandomFloat(-range, range),
                                                                      0 + generateRandomFloat(-range, range)),
                                                     engine::Vector3D());
                scenesAPI.addParticleDefault(currentParticle);
                particles.push_back(currentParticle);
            }

            // We get the sceneEngine
            std::shared_ptr<engine::Scene> sceneEngine = scenesAPI.getSceneEngine();

            // We add a cable spring between all of our particles
            int firstIndex = 1;
            for(auto& particle: particles)
            {
                // We add a cable spring with all the other particles
                std::shared_ptr<engine::CableSpring> cableSpring = std::make_shared<engine::CableSpring>(
                  particle, springConstant, restLength, elasticityLimitLength, restitutionCoef);
                for(int index = firstIndex; index < particlesNb; index++)
                {
                    sceneEngine->addForce(particles[index], cableSpring);
                }
                // We increase the starting index to avoid creating cablesprings twice
                firstIndex++;
            }

            // We add the gravity to all of our particles
            std::shared_ptr<engine::ParticleGravity> gravity = std::make_shared<engine::ParticleGravity>();
            sceneEngine->addForce(gravity);

            // We add drag to all of our particles
            std::shared_ptr<engine::ParticleDrag> drag = std::make_shared<engine::ParticleDrag>(k1, k2);
            sceneEngine->addForce(drag);

            // We add a wall to all of our particles, representing the floor at y = 0
            std::shared_ptr<engine::WallContactGenerator> wall =
              std::make_shared<engine::WallContactGenerator>(particles, engine::WallContactGenerator::y, 0.5, -1, 2);
            sceneEngine->addContactGenerator(wall);
        }
        ImGui::TreePop();
    }
}

void UserInterface::render(engine::GameEngine& gameEngine, api::ScenesAPI& scenesAPI, render::Camera& camera)
{
    float cameraAngle = camera.getFOVdeg();

    // Use a Begin/End pair to create a named window. create a window and append into it
    ImGui::Begin("Scene Editor");

    // Edit translation.x using a slider from 0.0f to 90.0f
    ImGui::SliderFloat("cameraAngle", &cameraAngle, 0.0f, 90.0f);

    showProjectileCreation(scenesAPI);

    moveBlob(scenesAPI);

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

void UserInterface::moveBlob(api::ScenesAPI& scenesAPI)
{
    std::vector<std::shared_ptr<engine::Particle>> particles = scenesAPI.getSceneEngine()->getParticles();

    if(particles.size() > 0)
    {
        ImGui::Text("Move First Particle");
        std::shared_ptr<engine::Particle> firstParticle = particles[0];

        // Edit translation.x using a slider from 0.0f to 90.0f
        ImGui::SliderFloat("X movement", &m_xMovement, -10, 10);
        ImGui::SliderFloat("Y movement", &m_yMovement, -10, 10);
        ImGui::SliderFloat("Z movement", &m_zMovement, -10, 10);

        // move only one particle from the blob
        firstParticle->setVelocity(firstParticle->getVelocity() +
                                   engine::Vector3D(m_xMovement, m_yMovement, m_zMovement));
    }
}

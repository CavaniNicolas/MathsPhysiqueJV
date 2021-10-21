
#include "PhysicsEngine/Bullet.hpp"
#include "PhysicsEngine/Fireball.hpp"
#include "PhysicsEngine/GameEngine.hpp"
#include "PhysicsEngine/Laser.hpp"

#include <Windows.h>
#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

void startEngineWithParticle(std::shared_ptr<Particle> particle, float duration)
{
    Scene scene = Scene({particle});
    GameEngine gameEngine = GameEngine(scene);

    gameEngine.run();

    float time = static_cast<float>(clock()) / CLOCKS_PER_SEC;
    float simulationEndTime = time + duration;

    while(time < simulationEndTime)
    {
        std::vector<Particle> particles = gameEngine.getParticles();
        for(Particle particle: particles)
        {
            std::cout << particle << std::endl;
        }
        Sleep(1000);
        time = static_cast<float>(clock()) / CLOCKS_PER_SEC;
    }

    gameEngine.stop();
}

int main()
{
    std::shared_ptr<Projectile> projectile;

    while(1)
    {
        std::cout << "There's 3 projectile types you can shoot. Which one do you want to use ?" << std::endl;
        std::cout << "- fireball (slow, negative gravity)" << std::endl;
        std::cout << "- bullet (fast, high gravity)" << std::endl;
        std::cout << "- laser (super fast, no gravity)" << std::endl;
        std::string projectileType;
        std::cout << "Your choice: ";
        std::cin >> projectileType;
        std::transform(projectileType.begin(), projectileType.end(), projectileType.begin(), tolower);
        if(projectileType == "laser")
        {
            projectile = std::shared_ptr<Projectile>(new Laser());
        }
        else if(projectileType == "bullet")
        {
            projectile = std::shared_ptr<Projectile>(new Bullet());
        }
        else if(projectileType == "fireball")
        {
            projectile = std::shared_ptr<Projectile>(new Fireball());
        }
        else
        {
            std::cerr << "This is not a valid type of projectile, please try again." << std::endl;
            continue;
        }

        std::cout << "Chose your initial position (example: (10,-2,6.5) ): ";
        Vector3D initialPosition = Vector3D::getVectorInput();
        projectile->setPosition(initialPosition);

        std::cout << "Chose the direction of your shoot (example: (10,-2,6.5) ): ";
        Vector3D direction = Vector3D::getVectorInput();
        projectile->setDirection(direction);

        std::cout << "Chose the simulation duration (in seconds): ";
        std::string timeStr;

        float duration;
        while(1)
        {
            try
            {
                std::cin >> timeStr;

                duration = std::stof(timeStr);

                if(duration <= 1)
                {
                    std::cout << "Please enter a time greater than 1 second, "
                                 "otherwise you won't see any print"
                              << std::endl;
                    std::cout << "Your new choice: ";
                }
                else
                {
                    // We have a valid duration
                    break;
                }
            }
            catch(std::invalid_argument)
            {
                std::cout << "Please enter a float value (for example 10, or 9.6)" << std::endl;
                std::cout << "Your new choice: ";
            }
        }

        startEngineWithParticle(projectile, duration);
    }
}

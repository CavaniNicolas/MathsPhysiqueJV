#include <iostream>
#include <Windows.h>

#include "PhysicsEngine/GameEngine.hpp"
#include "PhysicsEngine/Fireball.hpp"
#include "PhysicsEngine/Laser.hpp"
#include "PhysicsEngine/Bullet.hpp"

int main()
{
    int nbFireballs = 1;
    int nbLasers = 1;
    int nbBullets = 1;
    std::vector<Projectile *> projectiles;

    for (int i = 0; i < nbFireballs; i++) {
        projectiles.push_back(new Fireball(Vector3D(0, 100, 0), Vector3D(1, 0, 0), 6, 1));
    }
    for (int i = 0; i < nbLasers; i++) {
        projectiles.push_back(new Laser(Vector3D(0, 100, 0), Vector3D(1, 0, 0), 4, 1));
    }
    for (int i = 0; i < nbBullets; i++) {
        projectiles.push_back(new Bullet(Vector3D(0, 100, 0), Vector3D(1, 0, 0), 2, 1));
    }

    for (Projectile* projectile : projectiles) {
        std::cout << "Speed factor : " << projectile->getSpeedFactor() << std::endl;
        std::cout << "Initial velocity : " << projectile->getVelocity() << std::endl;
        std::cout << "Force : " << projectile->getForces()[0] << std::endl;
    }

    Scene scene = Scene(projectiles);

    GameEngine gameEngine = GameEngine(scene);

    gameEngine.run();

    float simulationTime = 10;
    float time = static_cast<float>(clock()) / CLOCKS_PER_SEC;
    float simulationEndTime = time + simulationTime;

    while (time < simulationEndTime) {
        std::vector<Particle> particles = gameEngine.getParticles();
        for (Particle particle : particles) {
            std::cout << particle << std::endl;
        }
        Sleep(1000);
        time = static_cast<float>(clock()) / CLOCKS_PER_SEC;
    }

    gameEngine.stop();
}

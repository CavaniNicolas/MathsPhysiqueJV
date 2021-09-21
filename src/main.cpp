
#include <iostream>
#include <vector>
#include <Windows.h>

#include "GameEngine.hpp"

int main()
{
    std::cout << "Hey\n";

    int nbParticles = 1;
    std::vector<Particle*> particles;

    std::vector<Vector3D> forces = { Vector3D(50, 0, 0) };
    for (int i = 0; i < nbParticles; i++) {
        particles.push_back(new Particle(Vector3D(), Vector3D(), forces, 1));
    }

    Scene scene = Scene(particles);

    GameEngine gameEngine = GameEngine(scene);

    gameEngine.run();

    Sleep(10000);

    gameEngine.stop();
}

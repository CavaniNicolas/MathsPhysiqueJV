
#include <iostream>
#include <vector>
#include <Windows.h>

#include "Particle.hpp"
#include "Vector3D.hpp"

int main()
{
    std::cout << "Hey\n";

    int nbParticles = 100000;
    std::vector<Particle*> particles;

    for (int i = 0; i < nbParticles; i++) {
        particles.push_back(new Particle(Vector3D(), Vector3D(), Vector3D(1, 1, 1), 0));
    }

    while (1) {
        for (Particle* particle : particles) {
            particle->integrate();
        }
        std::cout << "Position : " << particles[0]->getPosition() << std::endl;
        std::cout << "Velocity : " << particles[0]->getVelocity() << std::endl;
        std::cout << "Acceleration : " << particles[0]->getAcceleration() << std::endl;
        Sleep(17);
    }
}

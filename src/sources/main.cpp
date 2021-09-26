#include <iostream>
#include <string>
#include <algorithm>
#include <Windows.h>
#include "../headers/Fireball.hpp"
#include "../headers/Bullet.hpp"
#include "../headers/Laser.hpp"
#include "../headers/GameEngine.hpp"


void startEngineWithParticle(Particle* particle) {
	Scene scene = Scene({ particle });
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

int main() {
	Projectile* projectile;

	while (1) {
		std::cout << "There's 3 projectile types you can shoot. Which one do you want to use ?" << std::endl;
		std::cout << "- fireball (slow, negative gravity)" << std::endl;
		std::cout << "- bullet (fast, high gravity)" << std::endl;
		std::cout << "- laser (super fast, no gravity)" << std::endl;
		std::string projectileType;
		std::cout << "Your choice: ";
		std::cin >> projectileType;
		std::cout << std::endl;
		std::transform(projectileType.begin(), projectileType.end(), projectileType.begin(), tolower);
		std::cout << projectileType << std::endl;
		if (projectileType == "laser") {
			projectile = new Laser();
		}
		else if (projectileType == "bullet") {
			projectile = new Bullet();
		}
		else if (projectileType == "fireball") {
			projectile = new Fireball();
		}
		else {
			std::cerr << "This is not a valid type of projectile, please try again." << std::endl;
			continue;
		}

		std::cout << "Chose your initial position (example: (10,-2,6.5) ): ";
		Vector3D initialPosition = Vector3D::getVectorInput();
		projectile->setPosition(initialPosition);


		std::cout << "Chose the direction of your shoot (example: (10,-2,6.5) ): ";
		Vector3D direction = Vector3D::getVectorInput();
		projectile->setDirection(direction);

		startEngineWithParticle(projectile);
	}
}
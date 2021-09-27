#pragma once

#include "Projectile.hpp"

class Fireball : public Projectile {
private:
public:
	Fireball();

	Fireball(Vector3D initialPosition, Vector3D direction,
			 float damage, float radius, float damping = 0.999);

	Fireball(const Fireball& other);
};
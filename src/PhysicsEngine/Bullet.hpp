#pragma once

#include "Projectile.hpp"

class Bullet : public Projectile {
private:
public:
	Bullet();

	Bullet(Vector3D initialPosition, Vector3D direction,
		   float damage, float radius, float damping = 0.999);

	Bullet(const Bullet& other);
};
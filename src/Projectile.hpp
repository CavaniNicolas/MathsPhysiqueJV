#pragma once

#include "Particle.hpp"

class Projectile : public Particle {

private:
	float m_damage;
	float m_radius;
	float m_vanishTime;

public:
	Projectile(Vector3D initialPosition, Vector3D initialVelocity, vector<Vector3D> forces, 
			   float mass, float damping, float g, float damage, float radius, float vanishTime);

};
#pragma once

#include <time.h>
#include "Vector3D.hpp"

class Particle
{
private:
	float m_inverseMass;
	Vector3D m_position;
	Vector3D m_velocity;
	Vector3D m_acceleration;

	clock_t m_lastIntegrationTime;

public:
	//Constructors
	Particle(Vector3D position, Vector3D velocity, Vector3D acceleration, float inverseMass = 0.0);
	Particle();
	Particle(const Particle& other);
	
	//Assignation
	Particle& operator=(const Particle& other);
	
	float getInverseMass() const;
	Vector3D getPosition() const;
	Vector3D getVelocity() const;
	Vector3D getAcceleration() const;
	
	void setInverseMass(float mass);
	void setPosition(Vector3D position);
	void setVelocity(Vector3D velocity);
	void setAcceleration(Vector3D acceleration);
	
	void integrate();
};


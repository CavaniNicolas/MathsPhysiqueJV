#pragma once

#include <time.h>
#include <vector>
#include "Vector3D.hpp"

class Particle
{
private:
	float m_inverseMass;
    float m_damping;
    float m_g;
    Vector3D m_gravityForce;

	Vector3D m_position;
	Vector3D m_velocity;
	Vector3D m_acceleration;
	std::vector<Vector3D> m_forces;

public:
	//Constructors
	//Particle(Vector3D position, Vector3D velocity, Vector3D acceleration, float mass = 1, float g = 10, float damping = 0.999);
	Particle(Vector3D position, Vector3D velocity, std::vector<Vector3D> forces = {}, float mass = 1, float g = 10, float damping = 0.999);
	Particle();
	Particle(const Particle& other);
	
	//Assignation
	Particle& operator=(const Particle& other);
	
	float getInverseMass() const;
	float getMass() const;
	float getDamping() const;
	float getG() const;
	Vector3D getPosition() const;
	Vector3D getVelocity() const;
	Vector3D getAcceleration() const;
	std::vector<Vector3D> getForces() const;
	
	void setInverseMass(float inverseMass);
	void setMass(float mass);
	void setDamping(float damping);
	void setG(float g);
	void setPosition(Vector3D position);
	void setVelocity(Vector3D velocity);
	void setAcceleration(Vector3D acceleration);
	//void setAcceleration(Vector3D acceleration);
	void addForce(Vector3D force);
	void setForces(std::vector<Vector3D> forces);
	
	virtual void integrate(float deltaT);

	friend std::ostream& operator<<(std::ostream& out, Particle const& particle);
};


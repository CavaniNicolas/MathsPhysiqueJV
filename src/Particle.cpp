
#include "Particle.hpp"

//Constructors
Particle::Particle(Vector3D position, Vector3D velocity, Vector3D acceleration, float inverseMass) {
	m_position = position;
	m_velocity = velocity;
	m_acceleration = acceleration;
	m_inverseMass = inverseMass;

	m_lastIntegrationTime = 0;
}

Particle::Particle(): 
    Particle::Particle(Vector3D(), Vector3D(), Vector3D())
{}

Particle::Particle(const Particle& other): 
    Particle::Particle(other.m_position, other.m_velocity, other.m_acceleration, other.m_inverseMass)
{}

//Assignation
Particle& Particle::operator=(const Particle& other) {
    if (this != &other) {
        m_position = other.m_position;
        m_velocity = other.m_velocity;
        m_acceleration = other.m_acceleration;
        m_inverseMass = other.m_inverseMass;
    }
	return *this;
}

float Particle::getInverseMass() const {
	return m_inverseMass;
}

Vector3D Particle::getPosition() const {
	return m_position;
}

Vector3D Particle::getVelocity() const {
	return m_velocity;
}

Vector3D Particle::getAcceleration() const {
	return m_acceleration;
}

void Particle::setInverseMass(float mass) {
	m_inverseMass = mass;
}

void Particle::setPosition(Vector3D position) {
	m_position = position;
}

void Particle::setVelocity(Vector3D velocity) {
	m_velocity = velocity;
}

void Particle::setAcceleration(Vector3D acceleration) {
	m_acceleration = acceleration;
}

void Particle::integrate() {
	if (m_lastIntegrationTime != 0) {
		clock_t currentTime = clock();
	
        double deltaT = static_cast<float>(currentTime - m_lastIntegrationTime) / CLOCKS_PER_SEC;
        float powTerm = 0.5 * pow(deltaT, 2);

        m_position.setCoord(m_position.getX() + deltaT * m_velocity.getX() + powTerm * m_acceleration.getX(),
                            m_position.getY() + deltaT * m_velocity.getY() + powTerm * m_acceleration.getY(),
                            m_position.getZ() + deltaT * m_velocity.getZ() + powTerm * m_acceleration.getZ());
		m_velocity.setCoord(m_velocity.getX() + deltaT * m_acceleration.getX(),
							m_velocity.getY() + deltaT * m_acceleration.getY(),
							m_velocity.getZ() + deltaT * m_acceleration.getZ());
		m_lastIntegrationTime = currentTime;
	}
	else {
		m_lastIntegrationTime = clock();
	}
}

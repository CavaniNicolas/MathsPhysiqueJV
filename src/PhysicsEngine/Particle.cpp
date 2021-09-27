#include "Particle.hpp"

//// Constructors
//Particle::Particle(Vector3D position, Vector3D velocity, Vector3D acceleration, float mass, float g, float damping):
//    m_position(position),
//    m_velocity(velocity),
//    m_acceleration(acceleration),
//    m_inverseMass(1 / mass),
//    m_damping(damping),
//    m_g(g),
//    m_gravityForce(Vector3D(0, -m_g, 0)),
//    m_lastIntegrationTime(0)
//{
//}

Particle::Particle(Vector3D position, Vector3D velocity, std::vector<Vector3D> forces, float mass, float g, float damping):
    m_position(position),
    m_velocity(velocity),
    m_acceleration(Vector3D()),
    m_forces(forces),
    m_inverseMass(1 / mass),
    m_damping(damping),
    m_g(g),
    m_gravityForce(Vector3D(0, -m_g, 0)),
    m_lastIntegrationTime(0)
{
}

Particle::Particle(): 
	Particle::Particle(Vector3D(), Vector3D())
{}

Particle::Particle(const Particle& other): 
    Particle::Particle(other.m_position, other.m_velocity, other.m_forces, other.getMass(), other.m_g, other.m_damping)
{}

//Assignation
Particle& Particle::operator=(const Particle& other) {
    if (this != &other) {
        m_position = other.m_position;
        m_velocity = other.m_velocity;
        m_acceleration = other.m_acceleration;
        m_inverseMass = other.m_inverseMass;
		m_damping = other.m_damping;
		m_g = other.m_g;
		m_gravityForce = other.m_gravityForce;
    }
	return *this;
}

float Particle::getInverseMass() const {
	return m_inverseMass;
}

float Particle::getMass() const {
	return 1 / m_inverseMass;
}

float Particle::getDamping() const {
	return m_damping;
}

float Particle::getG() const {
	return m_g;
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

std::vector<Vector3D> Particle::getForces() const {
	return m_forces;
}

void Particle::setInverseMass(float inverseMass) {
	m_inverseMass = inverseMass;
}

void Particle::setMass(float mass) {
	m_inverseMass = 1 / mass;
}

void Particle::setDamping(float damping) {
	m_damping = damping;
}

void Particle::setG(float g) {
	m_g = g;
	m_gravityForce = Vector3D(0, -m_g, 0);
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

void Particle::addForce(Vector3D force) {
	m_forces.push_back(force);
}

// TO CHECK
void Particle::setForces(std::vector<Vector3D> forces) {
	m_forces.clear();
	m_forces = forces;
}

void Particle::integrate() {
	if (m_lastIntegrationTime != 0) {
		clock_t currentTime = clock();
	
        float deltaT = (float)(currentTime - m_lastIntegrationTime) / CLOCKS_PER_SEC;

		//Position update
        float powTerm = 0.5 * pow(deltaT, 2);
        m_position.setCoord(m_position.getX() + deltaT * m_velocity.getX() + powTerm * m_acceleration.getX(),
                            m_position.getY() + deltaT * m_velocity.getY() + powTerm * m_acceleration.getY(),
                            m_position.getZ() + deltaT * m_velocity.getZ() + powTerm * m_acceleration.getZ());

		//Resulting acceleration calculation
		Vector3D forcesSum = Vector3D();
		for (Vector3D force : m_forces) {
			forcesSum += force;
		}
		forcesSum *= m_inverseMass;
		forcesSum += m_gravityForce;

		setAcceleration(forcesSum);

		//Velocity update
		m_velocity.setCoord(m_velocity.getX() * pow(m_damping, deltaT) + deltaT * m_acceleration.getX(),
							m_velocity.getY() * pow(m_damping, deltaT) + deltaT * m_acceleration.getY(),
							m_velocity.getZ() * pow(m_damping, deltaT) + deltaT * m_acceleration.getZ());
		m_lastIntegrationTime = currentTime;
	}
	else {
		m_lastIntegrationTime = clock();
	}
}

std::ostream& operator<<(std::ostream& out, Particle const& particle) {
	out << "Position : " << particle.m_position << ", "
		<< "Velocity : " << particle.m_velocity;// << ", "
		//<< "Acceleration : "	<< particle.m_acceleration	<< ", "
		//<< "Forces : ";
	//for (Vector3D force : particle.m_forces) {
	//	out << force << " ";
	//}
	return out;
}

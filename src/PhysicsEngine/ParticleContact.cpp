#include "ParticleContact.hpp"

ParticleContact::ParticleContact(std::shared_ptr<Particle> particleA,
                                 std::shared_ptr<Particle> particleB,
                                 float restitution,
                                 float penetration,
                                 Vector3D contactNormal) :
    m_particle({particleA, particleB}), m_restitution(restitution), m_penetration(penetration), m_contactNormal(contactNormal)
{}

ParticleContact ::~ParticleContact() {
    m_particle.clear();
}

// Handle impulse for this collision
void ParticleContact::resolveVelocity() {
    Vector3D v1 = m_particle[0]->getVelocity();
    Vector3D v2 = m_particle[1]->getVelocity();
    Vector3D v_rel = v1 - v2;

    float inv_m1 = m_particle[0]->getInverseMass();
    float inv_m2 = m_particle[1]->getInverseMass();
    float k = ((v_rel * (m_restitution + 1)).scalarProduct(m_contactNormal)) / ((inv_m1 + inv_m2));

    m_particle[0]->setVelocity(v1 - m_contactNormal * k * inv_m1);
    m_particle[1]->setVelocity(v2 + m_contactNormal * k * inv_m2);
}

// Handle interpenetration for this collision
void ParticleContact::resolveInterpenetration()
{
    Vector3D p1 = m_particle[0]->getPosition();
    Vector3D p2 = m_particle[1]->getPosition();
    Vector3D delta_p1;
    Vector3D delta_p2;
    float m1 = m_particle[0]->getMass();
    float m2 = m_particle[1]->getMass();

    delta_p1 = m_contactNormal * m_penetration * (m2 / (m1 + m2));
    delta_p2 = m_contactNormal * m_penetration * (m1 / (m1 + m2));

    m_particle[0]->setPosition(p1 + delta_p1);
    m_particle[1]->setPosition(p2 + delta_p2);
}

// Resolve velocity and interpenetration
void ParticleContact::resolve(float duration) {
    resolveVelocity();
    resolveInterpenetration();
}

// Return the separationVelocity of the particles
float ParticleContact::calculateSeparatingVelocity() {
    if (m_particle[1]) 
    {
        Vector3D v_A = m_particle[0]->getVelocity();
        Vector3D v_B = m_particle[1]->getVelocity();
        return (v_A - v_B).scalarProduct(m_contactNormal.normalize());
    }
    else
    {
        Vector3D v_A = m_particle[0]->getVelocity();
        return (v_A).scalarProduct(m_contactNormal.normalize());
    }
}
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
    if(m_particle[1] != nullptr)
    {
        Vector3D v1 = m_particle[0]->getVelocity();
        Vector3D v2 = m_particle[1]->getVelocity();
        Vector3D v_rel = v1 - v2;

        float inv_m1 = m_particle[0]->getInverseMass();
        float inv_m2 = m_particle[1]->getInverseMass();
        float k = ((v_rel * (m_restitution + 1)).scalarProduct(m_contactNormal)) / ((inv_m1 + inv_m2));

        m_particle[0]->setVelocity(v1 - m_contactNormal * k * inv_m1);
        m_particle[1]->setVelocity(v2 + m_contactNormal * k * inv_m2);
    }
    else
    {
        //TO CHECK
        Vector3D velocity = m_particle[0]->getVelocity();

        Vector3D accel = m_particle[0]->getAcceleration();
        
        float inv_m = m_particle[0]->getInverseMass();
        float k = ((velocity * (m_restitution + 1)).scalarProduct(m_contactNormal)) / inv_m;


        Vector3D newVelocity = velocity - m_contactNormal * k * inv_m;

        bool restingParticle = false;
        if (accel == Vector3D(0, m_particle[0]->getG(), 0)) {
            if(newVelocity.getY() < 8 * m_restitution || m_restitution == 0)
            {
                std::cout << "Particle is resting" << std::endl;
                restingParticle = true;
            }
        }

        if(restingParticle)
        {
            newVelocity.setY(0);
            accel.setY(0);
            m_particle[0]->setAcceleration(accel);
            m_particle[0]->setResting(true);
        }
        m_particle[0]->setVelocity(newVelocity);

        
    }
}

// Handle interpenetration for this collision
void ParticleContact::resolveInterpenetration()
{
    if(m_particle[1] != nullptr)
    {
        Vector3D p1 = m_particle[0]->getPosition();
        Vector3D p2 = m_particle[1]->getPosition();
        Vector3D delta_p1;
        Vector3D delta_p2;
        float m1 = m_particle[0]->getMass();
        float m2 = m_particle[1]->getMass();

        delta_p1 = m_contactNormal * m_penetration * (m2 / (m1 + m2));
        delta_p2 = m_contactNormal * m_penetration * -(m1 / (m1 + m2));

        m_particle[0]->setPosition(p1 + delta_p1);
        m_particle[1]->setPosition(p2 + delta_p2);
        // Est-ce qu'il faudrait plutôt mettre p1/2 - delta_p1/2 ?
    }
    else
    {
        //TO CHECK
        Vector3D p1 = m_particle[0]->getPosition();
        Vector3D delta_p1;

        delta_p1 = m_contactNormal * m_penetration;

        m_particle[0]->setPosition(p1 + delta_p1);
    }
}

// Resolve velocity and interpenetration
void ParticleContact::resolve() {
    resolveInterpenetration();
    resolveVelocity();
}

// Return the separationVelocity of the particles
float ParticleContact::calculateSeparatingVelocity()
{
    if (m_particle[1] != nullptr) 
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

bool operator==(const std::shared_ptr<ParticleContact> c1, const std::shared_ptr<ParticleContact> c2)
{
    return c1->calculateSeparatingVelocity() == c2->calculateSeparatingVelocity();
}

bool operator!=(const std::shared_ptr<ParticleContact> c1, const std::shared_ptr<ParticleContact> c2)
{
    return c1->calculateSeparatingVelocity() != c2->calculateSeparatingVelocity();
}

bool operator<(const std::shared_ptr<ParticleContact> c1, const std::shared_ptr<ParticleContact> c2)
{
    return c1->calculateSeparatingVelocity() < c2->calculateSeparatingVelocity();
}

bool operator>(const std::shared_ptr<ParticleContact> c1, const std::shared_ptr<ParticleContact> c2)
{
    return c1->calculateSeparatingVelocity() > c2->calculateSeparatingVelocity();
}

bool operator<=(const std::shared_ptr<ParticleContact> c1, const std::shared_ptr<ParticleContact> c2)
{
    return c1->calculateSeparatingVelocity() <= c2->calculateSeparatingVelocity();
}

bool operator>=(const std::shared_ptr<ParticleContact> c1, const std::shared_ptr<ParticleContact> c2)
{
    return c1->calculateSeparatingVelocity() >= c2->calculateSeparatingVelocity();
}
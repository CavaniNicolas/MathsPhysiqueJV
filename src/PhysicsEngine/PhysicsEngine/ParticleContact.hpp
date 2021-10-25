#pragma once

#include <memory>

#include "PhysicsEngine/Particle.hpp"

namespace engine
{

class ParticleContact
{
  private:
    // Particle[0] => Particle A
    // Particle[1] => Particle B - Could be nullptr
    std::vector<std::shared_ptr<Particle>> m_particle;

    // value between 0 and 1
    // defining the elasticness of the collision
    float m_restitution;

    // distance of penetration of the contact
    float m_penetration;

    // normal of the contact
    Vector3D m_contactNormal;

    // Handle impulse for this collision
    void resolveVelocity();

    // Handle interpenetration for this collision
    void resolveInterpenetration();

  public:
    ParticleContact(std::shared_ptr<Particle> particleA,
                    std::shared_ptr<Particle> particleB,
                    float restitution,
                    float penetration,
                    Vector3D contactNormal);

    ~ParticleContact();

    // Resolve velocity and interpenetration
    void resolve();

    // Return the separationVelocity of the particles
    float calculateSeparatingVelocity();

    friend bool operator==(const std::shared_ptr<ParticleContact> c1, const std::shared_ptr<ParticleContact> c2);
    friend bool operator!=(const std::shared_ptr<ParticleContact> c1, const std::shared_ptr<ParticleContact> c2);

    friend bool operator<(const std::shared_ptr<ParticleContact> c1, const std::shared_ptr<ParticleContact> c2);
    friend bool operator>(const std::shared_ptr<ParticleContact> c1, const std::shared_ptr<ParticleContact> c2);

    friend bool operator<=(const std::shared_ptr<ParticleContact> c1, const std::shared_ptr<ParticleContact> c2);
    friend bool operator>=(const std::shared_ptr<ParticleContact> c1, const std::shared_ptr<ParticleContact> c2);

    // This is a required structure to tell the priority queue how to compare ParticleContact
    struct HighestSeparatingVelocity
    {
        bool operator()(const std::shared_ptr<ParticleContact> c1, const std::shared_ptr<ParticleContact> c2)
        {
            return c1 > c2;
        }
    };
};

} // namespace engine

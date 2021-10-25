#pragma once

#include "PhysicsEngine/ParticleContactGenerator.hpp"

class WallContactGenerator : public ParticleContactGenerator
{
  public:
    enum WallPlan
    {
        x,
        y,
        z
    };

    WallPlan m_wallPlan;
    float m_coordinates;
    float m_thickness;
    std::vector<std::shared_ptr<Particle>> m_particles;
    float m_restitution;

    WallContactGenerator(
      std::shared_ptr<Particle> particle, WallPlan wallPlan, float restitution, float coordinates, float thickness);

    WallContactGenerator(std::vector<std::shared_ptr<Particle>> particles,
                         WallPlan wallPlan,
                         float restitution,
                         float coordinates,
                         float thickness);

    unsigned int addContact(std::vector<std::shared_ptr<ParticleContact>>& contacts, unsigned int limit) const;

    float calculatePenetration(std::shared_ptr<Particle> particle) const;

    Vector3D calculateNormal(std::shared_ptr<Particle> particle) const;
};
#pragma once

#include "ParticleContactGenerator.hpp"

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
    std::shared_ptr<Particle> m_particle;
    float m_restitution;

    WallContactGenerator(
      std::shared_ptr<Particle> particle, WallPlan wallPlan, float restitution, float coordinates, float thickness);

    unsigned int addContact(std::vector<std::shared_ptr<ParticleContact>>& contacts, unsigned int limit) const;

    float calculatePenetration() const;

    Vector3D calculateNormal() const;
};
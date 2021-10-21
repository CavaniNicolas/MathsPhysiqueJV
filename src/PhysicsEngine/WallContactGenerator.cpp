#include "PhysicsEngine/WallContactGenerator.hpp"


WallContactGenerator::WallContactGenerator(std::shared_ptr<Particle> particle, WallPlan wallPlan,float restitution,
                                           float coordinates,
                                           float thickness):
  m_particle(particle), m_wallPlan(wallPlan), m_restitution(restitution),m_coordinates(coordinates), m_thickness(thickness){};


float WallContactGenerator::calculatePenetration() const{
    float wallcenterdistance;
    float penetration = 0;
    switch(m_wallPlan)
    {
        case x:
            wallcenterdistance = m_particle->getPosition().getX() - m_coordinates;
            if(std::abs(wallcenterdistance) < m_thickness / 2) {
                //contact with the wall
                if (wallcenterdistance > 0) {
                    penetration = std::abs(m_coordinates + m_thickness / 2 - m_particle->getPosition().getX());
                }
                else
                {
                    penetration = std::abs(m_coordinates - m_thickness / 2 - m_particle->getPosition().getX());
                }
            }
            break;
        case y:
            wallcenterdistance = m_particle->getPosition().getY() - m_coordinates;
            if(std::abs(wallcenterdistance) < m_thickness / 2)
            {
                // contact with the wall
                if(wallcenterdistance > 0)
                {
                    penetration = std::abs(m_coordinates + m_thickness / 2 - m_particle->getPosition().getY());
                }
                else
                {
                    penetration = std::abs(m_coordinates - m_thickness / 2 - m_particle->getPosition().getY());
                }
            }
            break;
        case z:
            wallcenterdistance = m_particle->getPosition().getZ() - m_coordinates;
            if(std::abs(wallcenterdistance) < m_thickness / 2)
            {
                // contact with the wall
                if(wallcenterdistance > 0)
                {
                    penetration = std::abs(m_coordinates + m_thickness / 2 - m_particle->getPosition().getZ());
                }
                else
                {
                    penetration = std::abs(m_coordinates - m_thickness / 2 - m_particle->getPosition().getZ());
                }
            }
            break;
        default: break;
    }
    return penetration;
}

Vector3D WallContactGenerator::calculateNormal() const {
    Vector3D normal;
    switch(m_wallPlan)
    {
        case x: 
            normal = m_particle->getPosition() - Vector3D(m_coordinates, m_particle->getPosition().getY(), m_particle->getPosition().getZ()).normalize();
            break;
        case y:
            normal =
              m_particle->getPosition() -
              Vector3D(m_particle->getPosition().getX(), m_coordinates, m_particle->getPosition().getZ()).normalize();
            break;
        case z:
            normal = m_particle->getPosition() -
                     Vector3D(m_particle->getPosition().getX(), m_particle->getPosition().getY(), m_coordinates).normalize();
            break;
        default: break;
    }
    return normal;  
 }

unsigned int WallContactGenerator::addContact(std::shared_ptr<std::vector<std::shared_ptr<ParticleContact>>> contacts,
                                              unsigned int limit) const
{
    float penetration = calculatePenetration();

    if (penetration > 0) {
        if(limit >= 1)
        {
            contacts->push_back(
              std::make_shared<ParticleContact>(m_particle, nullptr, m_restitution, penetration, calculateNormal()));
            return 1;
        }
    }
    return 0;

}
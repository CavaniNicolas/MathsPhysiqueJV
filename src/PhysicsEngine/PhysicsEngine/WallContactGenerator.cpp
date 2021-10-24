#include "PhysicsEngine/WallContactGenerator.hpp"

WallContactGenerator::WallContactGenerator(std::shared_ptr<Particle> particle, 
                                           WallPlan wallPlan, 
                                           float restitution, 
                                           float coordinates, 
                                           float thickness) :
  m_particles({particle}),
  m_wallPlan(wallPlan),
  m_restitution(restitution),
  m_coordinates(coordinates),
  m_thickness(thickness)
{};

WallContactGenerator::WallContactGenerator(std::vector<std::shared_ptr<Particle>> particles, 
                                           WallPlan wallPlan,
                                           float restitution,
                                           float coordinates,
                                           float thickness):
  m_particles(particles),
  m_wallPlan(wallPlan),
  m_restitution(restitution),
  m_coordinates(coordinates),
  m_thickness(thickness)
{};


float WallContactGenerator::calculatePenetration(std::shared_ptr<Particle> particle) const{
    float wallcenterdistance;
    float penetration = 0;
    float particleRadius = particle->getRadius();
    switch(m_wallPlan)
    {
        case x:
            wallcenterdistance = particle->getPosition().getX() - m_coordinates;
            if(std::abs(wallcenterdistance) - particleRadius < m_thickness / 2)
            {
                //contact with the wall
                if (wallcenterdistance > 0) {
                    penetration =
                      std::abs(m_coordinates + m_thickness / 2 - particle->getPosition().getX()) + particleRadius;
                }
                else
                {
                    penetration =
                      std::abs(m_coordinates - m_thickness / 2 - particle->getPosition().getX()) + particleRadius;
                }
            }
            break;
        case y:
            wallcenterdistance = particle->getPosition().getY() - m_coordinates;
            if(std::abs(wallcenterdistance) - particleRadius < m_thickness / 2)
            {
                // contact with the wall
                if(wallcenterdistance > 0)
                {
                    penetration =
                      std::abs(m_coordinates + m_thickness / 2 - particle->getPosition().getY()) + particleRadius;
                }
                else
                {
                    penetration =
                      std::abs(m_coordinates - m_thickness / 2 - particle->getPosition().getY()) + particleRadius;
                }
            }
            break;
        case z:
            wallcenterdistance = particle->getPosition().getZ() - m_coordinates;
            if(std::abs(wallcenterdistance) - particleRadius < m_thickness / 2)
            {
                // contact with the wall
                if(wallcenterdistance > 0)
                {
                    penetration =
                      std::abs(m_coordinates + m_thickness / 2 - particle->getPosition().getZ()) + particleRadius;
                }
                else
                {
                    penetration =
                      std::abs(m_coordinates - m_thickness / 2 - particle->getPosition().getZ()) + particleRadius;
                }
            }
            break;
        default: break;
    }
    return penetration;
}

Vector3D WallContactGenerator::calculateNormal(std::shared_ptr<Particle> particle) const
{
    Vector3D normal;
    switch(m_wallPlan)
    {
        case x: 
            normal = (particle->getPosition() - Vector3D(m_coordinates, particle->getPosition().getY(), particle->getPosition().getZ())).normalize();
            break;
        case y:
            normal =
              (particle->getPosition() -
              Vector3D(particle->getPosition().getX(), m_coordinates, particle->getPosition().getZ())).normalize();
            break;
        case z:
            normal = (particle->getPosition() -
                     Vector3D(particle->getPosition().getX(), particle->getPosition().getY(), m_coordinates)).normalize();
            break;
        default: break;
    }
    return normal;  
 }

unsigned int WallContactGenerator::addContact(std::vector<std::shared_ptr<ParticleContact>>& contacts,
                                              unsigned int limit) const
{
    std::cout << "trying to add wall contact" << std::endl;
    int tempLimit = limit;
    for (auto& particle : m_particles) {
        float penetration = calculatePenetration(particle);

        if(penetration > 0)
        {
            std::cout << "Wall contact detected" << std::endl;
            if(tempLimit >= 1)
            {
                tempLimit--;
                contacts.push_back(
                  std::make_shared<ParticleContact>(particle, nullptr, m_restitution, penetration, calculateNormal(particle)));
            }
        }
    }
    return limit - tempLimit;
}
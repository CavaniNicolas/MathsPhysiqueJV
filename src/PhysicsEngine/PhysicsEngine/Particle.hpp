#pragma once

#include <time.h>
#include <vector>

#include "PhysicsEngine/PhysicsObject.hpp"

#define M_PI 3.14159265358979323846 /* pi */

namespace engine
{

class Particle : public PhysicsObject
{
  private:
    float m_radius;

  public:
    // Constructors
    Particle(
      Vector3D position, Vector3D velocity, float radius = 1, float mass = 1, float g = 10, float damping = 0.999);
    Particle();
    Particle(const Particle& other);

    // Assignation
    Particle& operator=(const Particle& other);

    inline float getRadius() const;

    inline void setRadius(float radius);

    float calculateVolume();

    void integratePosition(float deltaT);
    void integrateVelocity(float deltaT);

    friend std::ostream& operator<<(std::ostream& out, Particle const& particle);
};

} // namespace engine

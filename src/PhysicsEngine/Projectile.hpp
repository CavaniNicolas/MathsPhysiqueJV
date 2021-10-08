#pragma once

#include "Particle.hpp"

class Projectile : public Particle
{
  private:
    float m_damage;
    float m_radius;
    float m_speedFactor;
    Vector3D m_direction;

  public:
    Projectile(float damage, float radius, float speedFactor);
    //    Projectile(float speedFactor, float radius, float mass, float g);

    Projectile();
    Projectile(Vector3D initialPosition,
               Vector3D direction,
               float speedFactor,
               float mass,
               float damage,
               float radius,
               float g = 10,
               float damping = 0.999);

    Projectile(const Projectile& other);

    float getDamage() const;
    float getRadius() const;
    float getSpeedFactor() const;
    Vector3D getDirection() const;

    void setDamage(float damage);
    void setRadius(float radius);
    void setDirection(Vector3D direction);
    void setSpeedFactor(float speedFactor);
};

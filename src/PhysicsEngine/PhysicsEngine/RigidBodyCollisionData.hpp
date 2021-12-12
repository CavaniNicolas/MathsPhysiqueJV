#pragma once

#include <vector>
#include "PhysicsEngine/RigidBodyContact.hpp"

namespace engine
{
class RigidBodyCollisionData
{
  private:
    std::vector<RigidBodyContact> m_contacts;
    int m_maxContacts;

  public:
    RigidBodyCollisionData(int maxContacts);

    std::vector<RigidBodyContact> getContacts() const;

    void addContact(RigidBodyContact& contact);
};
} // namespace engine
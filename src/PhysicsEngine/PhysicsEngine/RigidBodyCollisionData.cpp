#include "PhysicsEngine/RigidBodyCollisionData.hpp"

namespace engine
{
RigidBodyCollisionData::RigidBodyCollisionData(int maxContacts): m_maxContacts(maxContacts) {}

std::vector<RigidBodyContact> RigidBodyCollisionData::popContacts()
{
    std::vector<RigidBodyContact> contacts = m_contacts;
    m_contacts.clear();
    m_contacts.resize(0);
    return contacts;
}

int RigidBodyCollisionData::getMaxContacts() const
{
    return m_maxContacts;
}

void RigidBodyCollisionData::addContact(RigidBodyContact contact)
{
    if(m_contacts.size() < m_maxContacts)
    {
        m_contacts.push_back(contact);
    }
    else
    {
        std::cout << "MAX SIZE REACHED" << std::endl;
    }
}
} // namespace engine
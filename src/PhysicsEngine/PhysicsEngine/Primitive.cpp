#include "PhysicsEngine/Primitive.hpp"

namespace engine
{
Vector3D Primitive::getPosition() const
{
    Vector3D position = Vector3D();
    if(m_body != nullptr)
    {
        position = m_body->getPosition();
    }

    position = m_offset.transformPosition(position);

    return position;
}

Primitive::Primitive(std::shared_ptr<RigidBody> body, Matrix34 offset): m_body(body), m_offset(offset) {}

std::shared_ptr<RigidBody> Primitive::getRigidBody() const
{
    return m_body;
}
Matrix34 Primitive::getOffset() const
{
    return m_offset;
}

void Primitive::setRigidBody(std::shared_ptr<RigidBody> body)
{
    m_body = body;
}
void Primitive::setOffset(Matrix34 offset)
{
    m_offset = offset;
}
} // namespace engine
#include "PhysicsEngine/Primitive.hpp"

namespace engine
{
	Vector3D Primitive::getPosition() const {
        Vector3D position = Vector3D();
        if (m_body != nullptr) {
            position = m_body->getTransformationMatrix().transformPosition(position);
        }

        position = m_offset.transformPosition(position);

        return position;
    }
}
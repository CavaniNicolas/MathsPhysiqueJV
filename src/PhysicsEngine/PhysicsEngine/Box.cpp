#include "PhysicsEngine/Box.hpp"

namespace engine
{


float Box::getGreatestHalfSize() const
{
    float greatestHalfSize = std::max(m_halfSizes.getX(), m_halfSizes.getY());
    return std::max(greatestHalfSize, m_halfSizes.getZ());
}
} // namespace engine
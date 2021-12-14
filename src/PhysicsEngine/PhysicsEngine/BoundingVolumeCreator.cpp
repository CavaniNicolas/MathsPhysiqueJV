#include "PhysicsEngine/BoundingVolumeCreator.hpp"

namespace engine
{
bool BoundingVolumeCreator::containsPlan(const std::vector<std::shared_ptr<Primitive>>& primitives) {}

std::shared_ptr<BoundingVolume> BoundingVolumeCreator::createBoundingVolume(
  const std::vector<std::shared_ptr<Primitive>>& primitives)
{
    if(containsPlan(primitives))
    {
        // Trouver l'objet yMax et retourner un bounding plan de hauteur yMax
    }
    else
    {
        return std::make_shared<BoundingSphere>(primitives);
    }
}
} // namespace engine
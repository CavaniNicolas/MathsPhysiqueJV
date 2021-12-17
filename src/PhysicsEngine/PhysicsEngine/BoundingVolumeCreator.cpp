#include "PhysicsEngine/BoundingVolumeCreator.hpp"
#include "PhysicsEngine/Plan.hpp"

namespace engine
{
bool BoundingVolumeCreator::containsPlan(const std::vector<std::shared_ptr<Primitive>>& primitives) {
    for(const auto& primitive: primitives) {
        if (const std::shared_ptr<Plan>& plan = std::dynamic_pointer_cast<Plan>(primitive)) {
            return true;
        }
    }
    return false;
}

std::shared_ptr<BoundingVolume> BoundingVolumeCreator::createBoundingVolume(
  const std::vector<std::shared_ptr<Primitive>>& primitives)
{
    if(containsPlan(primitives))
    {
        float yMax = primitives[0]->getYMax();
        // Trouver l'objet yMax et retourner un bounding plan de hauteur yMax
        for(int i = 1; i < primitives.size(); i++)
        {
            yMax = std::max(yMax, primitives[i]->getYMax());
        }
        return std::make_shared<BoundingPlan>(yMax, primitives);
    }
    else
    {
        return std::make_shared<BoundingSphere>(primitives);
    }
}
} // namespace engine
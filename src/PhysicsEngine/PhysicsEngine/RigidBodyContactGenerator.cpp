#include "PhysicsEngine/RigidBodyContactGenerator.hpp"
#include "PhysicsEngine/Plan.hpp"
#include "PhysicsEngine/Box.hpp"

namespace engine
{
void RigidBodyContactGenerator::generateContact(const std::shared_ptr<Primitive>& prim1,
                                                const std::shared_ptr<Primitive>& prim2,
                                                RigidBodyCollisionData& collisionData)
{
    if(const std::shared_ptr<Plan>& plan = std::dynamic_pointer_cast<Plan>(prim1))
    {
        if(const std::shared_ptr<Box>& box = std::dynamic_pointer_cast<Box>(prim2))
        {
            box->generateContactWith(prim1, collisionData);
        }
        else
        {
            std::cerr << "We can only generate contacts between a bow and a plan" << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    else if(const std::shared_ptr<Box>& box = std::dynamic_pointer_cast<Box>(prim1))
    {
        if(const std::shared_ptr<Plan>& plan = std::dynamic_pointer_cast<Plan>(prim2))
        {
            box->generateContactWith(prim2, collisionData);
        }
        else
        {
            std::cerr << "We can only generate contacts between a bow and a plan" << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        std::cerr << "We can only generate contacts between a bow and a plan" << std::endl;
        exit(EXIT_FAILURE);
    }
}
} // namespace engine
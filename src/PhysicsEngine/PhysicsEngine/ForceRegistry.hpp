#pragma once

#include <vector>
#include "PhysicsEngine/ForceGenerator.hpp"

namespace engine
{
class ForceRegistry
{
  private:
    struct ForceEntry
    {
        std::weak_ptr<PhysicsObject> object;
        std::shared_ptr<ForceGenerator> forceGenerator;
    };

    using Registry = std::vector<ForceEntry>;
    Registry m_registry;

  public:
    // Constructors
    ForceRegistry(Registry registry = {});
    ForceRegistry(const ForceRegistry& other);
    // Destructor
    ~ForceRegistry();

    ForceRegistry& operator=(const ForceRegistry& other);

    // Setters
    void addEntry(std::shared_ptr<PhysicsObject> object, std::shared_ptr<ForceGenerator> forceGenerator);
    void setRegistry(Registry newRegistry);

    // Getters
    Registry getRegistry();

    void updateForce(float duration);
};

} // namespace engine

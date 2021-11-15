#include "PhysicsEngine/RigidBodyGravity.hpp"

using namespace engine;

// Apply the gravity force to center of mass of the rigidbody
void RigidBodyGravity::updateForce(std::shared_ptr<PhysicsObject> object, float duration)
{
    auto rigidBody = checkRigidBody(object);

    rigidBody->addForce(Vector3D(0, -rigidBody->getG(), 0) * rigidBody->getMass());
}
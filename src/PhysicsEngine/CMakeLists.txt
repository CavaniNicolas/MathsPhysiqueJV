
set(MP_PHYSICS_LIB_NAME PhysicsEngineLib)

set(SOURCES
    PhysicsEngine/GameEngine.cpp
    PhysicsEngine/Particle.cpp
    PhysicsEngine/Scene.cpp
    PhysicsEngine/Vector3D.cpp
    PhysicsEngine/PhysicsObject.cpp

    # Projectiles
    PhysicsEngine/Bullet.cpp
    PhysicsEngine/Fireball.cpp
    PhysicsEngine/Projectile.cpp
    PhysicsEngine/Laser.cpp

    # Forces
    PhysicsEngine/ParticleAnchoredSpring.cpp
    PhysicsEngine/ParticleBungeeSpring.cpp
    PhysicsEngine/ParticleBuoyancy.cpp
    PhysicsEngine/ParticleDrag.cpp
    PhysicsEngine/ForceRegistry.cpp
    PhysicsEngine/ParticleGravity.cpp
    PhysicsEngine/ParticleSpring.cpp
    PhysicsEngine/CableSpring.cpp

    # Collisions
    PhysicsEngine/ParticleContact.cpp
    PhysicsEngine/ParticleContactResolver.cpp
    PhysicsEngine/ParticleLink.cpp
    PhysicsEngine/ParticleCable.cpp
    PhysicsEngine/ParticleRod.cpp
    PhysicsEngine/WallContactGenerator.cpp

    # Rigidbodies
    PhysicsEngine/Matrix33.cpp
    PhysicsEngine/Matrix34.cpp
    PhysicsEngine/Quaternion.cpp
    PhysicsEngine/RigidBody.cpp
    PhysicsEngine/RigidBodyGravity.cpp
    PhysicsEngine/RigidBodySpring.cpp

    # Rigidbodies collisions
    PhysicsEngine/BoundingSphere.cpp
    PhysicsEngine/BoundingVolume.cpp
    PhysicsEngine/BoundingPlan.cpp
    PhysicsEngine/BoundingVolumeCreator.cpp
    PhysicsEngine/BVH.cpp
    PhysicsEngine/RigidBodyContact.cpp
    PhysicsEngine/RigidBodyCollisionData.cpp
    PhysicsEngine/Primitive.cpp
    PhysicsEngine/Plan.cpp
    PhysicsEngine/Box.cpp
    PhysicsEngine/RigidBodyContactGenerator.cpp
    PhysicsEngine/RigidBodyContactResolver.cpp

)

set(HEADERS
    PhysicsEngine/GameEngine.hpp
    PhysicsEngine/Particle.hpp
    PhysicsEngine/Scene.hpp
    PhysicsEngine/Vector3D.hpp
    PhysicsEngine/PhysicsObject.hpp
    PhysicsEngine/ForceGenerator.hpp

    # Projectiles
    PhysicsEngine/Bullet.hpp
    PhysicsEngine/Laser.hpp
    PhysicsEngine/Projectile.hpp
    PhysicsEngine/Fireball.hpp

    # Forces
    PhysicsEngine/ParticleAnchoredSpring.hpp
    PhysicsEngine/ParticleBungeeSpring.hpp
    PhysicsEngine/ParticleBuoyancy.hpp
    PhysicsEngine/ParticleDrag.hpp
    PhysicsEngine/ParticleForceGenerator.hpp
    PhysicsEngine/ForceRegistry.hpp
    PhysicsEngine/ParticleGravity.hpp
    PhysicsEngine/ParticleSpring.hpp
    PhysicsEngine/CableSpring.hpp

    # Collisions
    PhysicsEngine/ParticleCable.hpp
    PhysicsEngine/ParticleContact.hpp
    PhysicsEngine/ParticleContactGenerator.hpp
    PhysicsEngine/ParticleContactResolver.hpp
    PhysicsEngine/ParticleLink.hpp
    PhysicsEngine/ParticleRod.hpp
    PhysicsEngine/WallContactGenerator.hpp

    # Rigidbodies
    PhysicsEngine/Matrix33.hpp
    PhysicsEngine/Matrix34.hpp
    PhysicsEngine/Quaternion.hpp
    PhysicsEngine/RigidBody.hpp
    PhysicsEngine/RigidBodyForceGenerator.hpp
    PhysicsEngine/RigidBodyGravity.hpp
    PhysicsEngine/RigidBodySpring.hpp

    # Rigidbodies collisions
    PhysicsEngine/BoundingSphere.hpp
    PhysicsEngine/BoundingVolume.hpp
    PhysicsEngine/BoundingPlan.hpp
    PhysicsEngine/BoundingVolumeCreator.hpp
    PhysicsEngine/BVH.hpp
    PhysicsEngine/RigidBodyContact.hpp
    PhysicsEngine/RigidBodyCollisionData.hpp
    PhysicsEngine/Primitive.hpp
    PhysicsEngine/Plan.hpp
    PhysicsEngine/Box.hpp
    PhysicsEngine/RigidBodyContactGenerator.hpp
    PhysicsEngine/RigidBodyContactResolver.hpp
)

set(SOURCES_DEBUG
    PhysicsEngine/DebugUtils/ParticlePrinter.cpp
    PhysicsEngine/DebugUtils/RigidBodyPrinter.cpp
)

set(HEADERS_DEBUG
    PhysicsEngine/DebugUtils/ParticlePrinter.hpp
    PhysicsEngine/DebugUtils/RigidBodyPrinter.hpp
)

add_library(${MP_PHYSICS_LIB_NAME} STATIC
    ${SOURCES}
    ${HEADERS}
    ${SOURCES_DEBUG}
    ${HEADERS_DEBUG}
)

target_include_directories(${MP_PHYSICS_LIB_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

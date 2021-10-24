
set(MP_PHYSICS_LIB_NAME PhysicsEngineLib)

set(SOURCES
    PhysicsEngine/GameEngine.cpp
    PhysicsEngine/Particle.cpp
    PhysicsEngine/Scene.cpp
    PhysicsEngine/Vector3D.cpp

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
    PhysicsEngine/ParticleForceRegistry.cpp
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
)

set(HEADERS
    PhysicsEngine/GameEngine.hpp
    PhysicsEngine/Particle.hpp
    PhysicsEngine/Scene.hpp
    PhysicsEngine/Vector3D.hpp

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
    PhysicsEngine/ParticleForceRegistry.hpp
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
)

set(SOURCES_DEBUG
    PhysicsEngine/DebugUtils/ParticlePrinter.cpp
)

set(HEADERS_DEBUG
    PhysicsEngine/DebugUtils/ParticlePrinter.hpp
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

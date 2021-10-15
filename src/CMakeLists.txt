set(MP_EXE_NAME MathsPhysique)

set(SOURCES
    main.cpp
    PhysicsEngine/Bullet.cpp
    PhysicsEngine/Fireball.cpp
    PhysicsEngine/GameEngine.cpp
    PhysicsEngine/Laser.cpp
    PhysicsEngine/Particle.cpp
    PhysicsEngine/Projectile.cpp
    PhysicsEngine/Scene.cpp
    PhysicsEngine/Vector3D.cpp
    PhysicsEngine/ParticleForceGenerator.cpp
    PhysicsEngine/ParticleForceRegistry.cpp
    PhysicsEngine/ParticleBuoyancy.cpp
    PhysicsEngine/ParticleAnchoredSpring.hpp)

set(HEADERS
    PhysicsEngine/Bullet.hpp
    PhysicsEngine/GameEngine.hpp
    PhysicsEngine/Laser.hpp
    PhysicsEngine/Projectile.hpp
    PhysicsEngine/Particle.hpp
    PhysicsEngine/Fireball.hpp
    PhysicsEngine/Scene.hpp
    PhysicsEngine/Vector3D.hpp
    PhysicsEngine/ParticleForceGenerator.hpp
    PhysicsEngine/ParticleForceRegistry.hpp
    PhysicsEngine/ParticleBuoyancy.hpp 
    PhysicsEngine/ParticleAnchoredSpring.hpp)

add_executable(${MP_EXE_NAME} ${SOURCES} ${HEADERS})

#target_link_libraries(${MP_EXE_NAME} PRIVATE
#    # libs
#)

target_include_directories(${MP_EXE_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

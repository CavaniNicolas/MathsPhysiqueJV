set(MP_EXE_NAME MathsPhysique)

set(SOURCES
        sources/main.cpp
        sources/Particle.cpp
        sources/Vector3D.cpp
        sources/Scene.cpp
        sources/GameEngine.cpp
        sources/Projectile.cpp
        sources/Bullet.cpp
        sources/Fireball.cpp
        sources/Laser.cpp
)

set(HEADERS
        headers/Particle.hpp
        headers/Vector3D.hpp
        headers/Scene.hpp
        headers/GameEngine.hpp
        headers/Projectile.hpp
        headers/Fireball.hpp
        headers/Bullet.hpp
        headers/Laser.hpp
)

add_executable(${MP_EXE_NAME} ${SOURCES} ${HEADERS})

#target_link_libraries(${MP_EXE_NAME} PRIVATE
#    # libs
#)

target_include_directories(${MP_EXE_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)
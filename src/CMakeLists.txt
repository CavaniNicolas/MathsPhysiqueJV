set(MP_EXE_NAME MathsPhysique)

set(SOURCES
        main.cpp
        Particle.cpp
        Vector3D.cpp
        Scene.cpp
        GameEngine.cpp
)

set(HEADERS
        Particle.hpp
        Vector3D.hpp
        Scene.hpp
        GameEngine.hpp
)

add_executable(${MP_EXE_NAME} ${SOURCES} ${HEADERS})

#target_link_libraries(${MP_EXE_NAME} PRIVATE
#    # libs
#)

target_include_directories(${MP_EXE_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

set(MP_EXE_NAME MathsPhysique)

find_package(OpenGL REQUIRED)



# The CONFIG flag makes sure you get OGRE instead of OGRE-next
find_package(OGRE REQUIRED COMPONENTS Bites RTShaderSystem CONFIG)

# add the source files as usual
add_executable(0_Bootstrap src/Bootstrap.cpp)

# this also sets the includes and pulls third party dependencies
target_link_libraries(0_Bootstrap OgreBites OgreRTShaderSystem)



set(SOURCES
        main.cpp
        Vector3D.cpp
)

set(HEADERS
        Vector3D.hpp
)

add_executable(${MP_EXE_NAME} ${SOURCES} ${HEADERS})


target_link_libraries(${MP_EXE_NAME}
    ${OPENGL_LIBRARIES}
    OpenGL::GL
)

target_include_directories(${MP_EXE_NAME} PUBLIC
#        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${OPENGL_INCLUDE_DIRS}
)

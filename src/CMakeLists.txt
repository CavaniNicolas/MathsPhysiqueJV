
set(MP_EXE_NAME MathsPhysique)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

find_package(OpenGL REQUIRED)


set(SOURCES
        main.cpp
        Vector3D.cpp
)

set(HEADERS
        Vector3D.hpp
)

add_subdirectory("glfw-3.3.4")

add_executable(${MP_EXE_NAME} ${SOURCES} ${HEADERS})


target_link_libraries(${MP_EXE_NAME}
    ${OPENGL_LIBRARIES}
    OpenGL::GL
    glfw
)

target_include_directories(${MP_EXE_NAME} PUBLIC
#        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${OPENGL_INCLUDE_DIRS}
        ${GLFW3_INCLUDE_DIR}
)

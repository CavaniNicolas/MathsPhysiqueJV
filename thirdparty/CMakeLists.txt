
# glfw sources (3.3.4) :
# https://github.com/glfw/glfw
# glew sources (2.2.0) :
# https://github.com/nigels-com/glew

### GLFW and GLEW include dirs for the main project ###

set(MP_INC_DIRS
    "${CMAKE_CURRENT_SOURCE_DIR}/glfw-3.3.4/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/glew-2.2.0/include"
#    "glfw-3.3.4/include"
#    "glew-2.2.0/include"
    PARENT_SCOPE
)

### GLFW ###

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory("glfw-3.3.4")

### GLEW ###

set(GLEW_SOURCES
    glew-2.2.0/src/glew.c
)

add_library(GLEW_220 STATIC
    ${GLEW_SOURCES}
)

target_link_libraries(GLEW_220
    ${OPENGL_LIBRARIES}
)

target_include_directories(GLEW_220 PUBLIC
    glew-2.2.0/include
)

target_compile_definitions(GLEW_220 PUBLIC
    -DTW_STATIC
    -DTW_NO_LIB_PRAGMA
    -DTW_NO_DIRECT3D
    -DGLEW_STATIC
    -D_CRT_SECURE_NO_WARNINGS
)

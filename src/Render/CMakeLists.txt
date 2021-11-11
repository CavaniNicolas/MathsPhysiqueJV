
set(MP_RENDER_LIB_NAME RenderLib)

set(SOURCES
    Render/Camera.cpp
    Render/IndexBuffer.cpp
    Render/Mesh.cpp
    Render/RenderedMesh.cpp
    Render/Renderer.cpp
    Render/Scene.cpp
    Render/Shader.cpp
    Render/Texture.cpp
    Render/VertexArray.cpp
    Render/VertexBuffer.cpp
    Render/VertexBufferLayout.cpp
    Render/Window.cpp

    Render/Mesh/Plan.cpp
    Render/Mesh/Pyramid.cpp

    Render/Data/OBJReader.cpp
)

set(HEADERS
    Render/Camera.hpp
    Render/IndexBuffer.hpp
    Render/Mesh.hpp
    Render/RenderedMesh.hpp
    Render/Renderer.hpp
    Render/Scene.hpp
    Render/Shader.hpp
    Render/Texture.hpp
    Render/VertexArray.hpp
    Render/VertexBuffer.hpp
    Render/VertexBufferLayout.hpp
    Render/Window.hpp

    Render/Mesh/MeshModel.hpp
    Render/Mesh/Plan.hpp
    Render/Mesh/Pyramid.hpp

    Render/Data/OBJReader.hpp
)

add_library(${MP_RENDER_LIB_NAME} STATIC
    ${SOURCES}
    ${HEADERS}
)

set(MP_OPENGL_LINK_LIBS
    ${OPENGL_LIBRARY}
    glfw
    GLEW_220
)

target_link_libraries(${MP_RENDER_LIB_NAME}
    ${MP_OPENGL_LINK_LIBS}
    VendorLib
)

target_include_directories(${MP_RENDER_LIB_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${MP_INC_DIRS}
)

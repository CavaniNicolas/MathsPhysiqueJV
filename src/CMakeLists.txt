

set(MP_EXE_NAME MathsPhysique)

set(MP_LINK_LIBS
    ${OPENGL_LIBRARY}
    glfw
    GLEW_220
)

set(SOURCES
        main.cpp
        Vector3D.cpp
        Render/Camera.cpp
        Render/IndexBuffer.cpp
        Render/Mesh.cpp
        Render/RenderedMesh.cpp
        Render/Renderer.cpp
        Render/Shader.cpp
        Render/Texture.cpp
        Render/VertexArray.cpp
        Render/VertexBuffer.cpp

        vendor/imgui/
        vendor/imgui/imgui.cpp
        vendor/imgui/imgui_demo.cpp
        vendor/imgui/imgui_draw.cpp
        vendor/imgui/imgui_impl_glfw.cpp
        vendor/imgui/imgui_impl_opengl3.cpp
        vendor/imgui/imgui_tables.cpp
        vendor/imgui/imgui_widgets.cpp

        vendor/stb_image/stb_image.cpp
)

set(HEADERS
        Vector3D.hpp
        Render/Camera.hpp
        Render/IndexBuffer.hpp
        Render/Mesh.hpp
        Render/RenderedMesh.hpp
        Render/Renderer.hpp
        Render/Shader.hpp
        Render/Texture.hpp
        Render/VertexArray.hpp
        Render/VertexBuffer.hpp
        Render/VertexBufferLayout.hpp
        vendor/stb_image/stb_image.h
)

#add_definitions(
#    -DTW_STATIC
#    -DTW_NO_LIB_PRAGMA
#    -DTW_NO_DIRECT3D
#    -DGLEW_STATIC
#    -D_CRT_SECURE_NO_WARNINGS
#)

add_executable(${MP_EXE_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${MP_EXE_NAME}
    ${MP_LINK_LIBS}
)

target_include_directories(${MP_EXE_NAME} PUBLIC
    $<BUILD_INTERFACE:
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${OPENGL_INCLUDE_DIRS}
        ${MP_INC_DIRS}
        "vendor"
    >
)

message("{MP_INC_DIRS} ${MP_INC_DIRS}")

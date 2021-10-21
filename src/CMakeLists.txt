
set(MP_EXE_NAME MathsPhysique)

set(MP_LINK_LIBS
    ${OPENGL_LIBRARY}
    glfw
    GLEW_220
)

set(SOURCES
    main.cpp

    PhysicsEngine/Bullet.cpp
    PhysicsEngine/Fireball.cpp
    PhysicsEngine/GameEngine.cpp
    PhysicsEngine/Laser.cpp
    PhysicsEngine/Particle.cpp
    PhysicsEngine/ParticleAnchoredSpring.cpp
    PhysicsEngine/ParticleBungeeSpring.cpp
    PhysicsEngine/ParticleBuoyancy.cpp
    PhysicsEngine/ParticleDrag.cpp
    PhysicsEngine/ParticleForceGenerator.cpp
    PhysicsEngine/ParticleForceRegistry.cpp
    PhysicsEngine/Projectile.cpp
    PhysicsEngine/Scene.cpp
    PhysicsEngine/Vector3D.cpp

    Render/Camera.cpp
    Render/IndexBuffer.cpp
    Render/Mesh.cpp
    Render/RenderedMesh.cpp
    Render/Renderer.cpp
    Render/Shader.cpp
    Render/Texture.cpp
    Render/UserInterface.cpp
    Render/VertexArray.cpp
    Render/VertexBuffer.cpp
    Render/VertexBufferLayout.cpp
    Render/Window.cpp

    vendor/imgui/
    vendor/imgui/imgui.cpp
    vendor/imgui/imgui_demo.cpp
    vendor/imgui/imgui_draw.cpp
    vendor/imgui/imgui_impl_glfw.cpp
    vendor/imgui/imgui_impl_opengl3.cpp
    vendor/imgui/imgui_tables.cpp
    vendor/imgui/imgui_widgets.cpp

    vendor/stb_image/stb_image.cpp
    PhysicsEngine/ParticleContact.cpp
    PhysicsEngine/ParticleContactResolver.cpp
    PhysicsEngine/ParticleLink.cpp

set(HEADERS
    PhysicsEngine/Bullet.hpp
    PhysicsEngine/GameEngine.hpp
    PhysicsEngine/Laser.hpp
    PhysicsEngine/Projectile.hpp
    PhysicsEngine/Particle.hpp
    PhysicsEngine/ParticleAnchoredSpring.hpp
    PhysicsEngine/ParticleBungeeSpring.hpp
    PhysicsEngine/ParticleBuoyancy.hpp
    PhysicsEngine/ParticleDrag.hpp
    PhysicsEngine/ParticleForceGenerator.hpp
    PhysicsEngine/ParticleForceRegistry.hpp
    PhysicsEngine/Fireball.hpp
    PhysicsEngine/Scene.hpp
    PhysicsEngine/Vector3D.hpp

    Render/Camera.hpp
    Render/IndexBuffer.hpp
    Render/Mesh.hpp
    Render/RenderedMesh.hpp
    Render/Renderer.hpp
    Render/Shader.hpp
    Render/Texture.hpp
    Render/UserInterface.hpp
    Render/VertexArray.hpp
    Render/VertexBuffer.hpp
    Render/VertexBufferLayout.hpp
    Render/Window.hpp

    vendor/stb_image/stb_image.h
    PhysicsEngine/ParticleContact.hpp
    PhysicsEngine/ParticleContactResolver.hpp
    PhysicsEngine/ParticleContactGenerator.hpp
    PhysicsEngine/ParticleLink.hpp

#add_definitions(
#    -DTW_STATIC
#    -DTW_NO_LIB_PRAGMA
#    -DTW_NO_DIRECT3D
#    -DGLEW_STATIC
#    -D_CRT_SECURE_NO_WARNINGS
#)

set(IMGUI_COMPILE_FLAGS
      "-DIMGUI_USE_GLEW -DIMGUI_USE_GLFW_BINDING")
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
        "vendor/imgui"
    >
)
target_compile_definitions(${MP_EXE_NAME} PRIVATE -DRESOURCE_PATH="${CMAKE_SOURCE_DIR}/res/" ${IMGUI_COMPILE_FLAGS})

message("{MP_INC_DIRS} ${MP_INC_DIRS}")

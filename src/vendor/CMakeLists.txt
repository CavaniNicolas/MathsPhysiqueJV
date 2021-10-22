
set(MP_VENDOR_LIB_NAME VendorLib)

set(SOURCES
    imgui/
    imgui/imgui.cpp
    imgui/imgui_demo.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_impl_glfw.cpp
    imgui/imgui_impl_opengl3.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_widgets.cpp
    stb_image/stb_image.cpp
)

set(HEADERS
    stb_image/stb_image.h
)

set(IMGUI_COMPILE_FLAGS
      "-DIMGUI_USE_GLEW -DIMGUI_USE_GLFW_BINDING")

add_library(${MP_VENDOR_LIB_NAME} STATIC
    ${SOURCES}
    ${HEADERS}
)

target_link_libraries(${MP_VENDOR_LIB_NAME}
    glfw
)

target_include_directories(${MP_VENDOR_LIB_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    "imgui"
)

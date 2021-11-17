
set(MP_API_LIB_NAME APILib)

set(SOURCES
    API/PhysicsObjectMeshRegistry.cpp
    API/ScenesAPI.cpp
    API/UserInterface.cpp
)

set(HEADERS
    API/PhysicsObjectMeshRegistry.hpp
    API/ScenesAPI.hpp
    API/UserInterface.hpp
)

add_library(${MP_API_LIB_NAME} STATIC
    ${SOURCES}
    ${HEADERS}
)

target_link_libraries(${MP_API_LIB_NAME}
    VendorLib
    PhysicsEngineLib
    RenderLib
)

target_include_directories(${MP_API_LIB_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_definitions(${MP_API_LIB_NAME} PRIVATE -DRESOURCE_PATH="${CMAKE_SOURCE_DIR}/res/" ${IMGUI_COMPILE_FLAGS})

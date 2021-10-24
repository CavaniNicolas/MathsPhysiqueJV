
set(MP_API_LIB_NAME APILib)

set(SOURCES
    API/ParticleMeshRegistry.cpp
    API/ScenesAPI.cpp
    API/UserInterface.cpp
)

set(HEADERS
    API/ParticleMeshRegistry.hpp
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

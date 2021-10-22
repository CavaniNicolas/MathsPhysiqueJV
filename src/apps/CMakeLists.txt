
set(SOURCES
    main.cpp
)

set(HEADERS
)

add_executable(${MP_EXE_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${MP_EXE_NAME}
    VendorLib
    PhysicsEngineLib
    RenderLib
    APILib
)

target_include_directories(${MP_EXE_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_definitions(${MP_EXE_NAME} PRIVATE -DRESOURCE_PATH="${CMAKE_SOURCE_DIR}/res/" ${IMGUI_COMPILE_FLAGS})

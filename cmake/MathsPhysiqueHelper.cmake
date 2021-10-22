
#
# Create a new executable
#
# Usage:
#   mp_add_executable(<software_name>
#                SOURCE <source>
#                [INCLUDE_DIRS [item1...] ]
#                [LINKS [item1...] ])
#
# software_name name of the created executable
# SOURCE is the source of the executable
# LINKS an optional list of target/libraries to link with
# INCLUDE_DIRS an optional list of include directories
#
function(mp_add_executable software_name)
    set(options "")
    set(singleValues "")
    set(multipleValues SOURCE LINKS INCLUDE_DIRS)

    cmake_parse_arguments(SOFTWARE "${options}" "${singleValues}" "${multipleValues}" ${ARGN})

    add_executable(${software_name} ${SOFTWARE_SOURCE})

    target_link_libraries(${software_name} PUBLIC
        ${SOFTWARE_LINKS}
    )

    target_include_directories(${software_name} PUBLIC
        ${SOFTWARE_INCLUDE_DIRS}
    )

    target_compile_definitions(${software_name} PRIVATE -DRESOURCE_PATH="${CMAKE_SOURCE_DIR}/res/" ${IMGUI_COMPILE_FLAGS})

endfunction()

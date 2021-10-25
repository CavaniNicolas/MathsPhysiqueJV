
cmake_minimum_required(VERSION 3.16)

project(MathsPhysique
        VERSION 1.0.0
        LANGUAGES CXX C
)

find_package(OpenGL REQUIRED)

include(cmake/MathsPhysiqueHelper.cmake)

option(BUILD_TESTS "Build test executables" OFF)

add_subdirectory(thirdparty)

add_subdirectory(src)

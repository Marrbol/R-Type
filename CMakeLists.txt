##
## RType
##
## Root CMakeLists.txt
##

cmake_minimum_required(VERSION 3.10)

project(RType)

# Minimum C++ standard required
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output directories
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "cmake/")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(SFML 2.5 REQUIRED COMPONENTS graphics window system audio)

set(SOURCES
    src/Main.cpp

    src/Core/Core.cpp
    src/Core/Registry.cpp
    src/Core/SparseArray.cpp

    src/GUI/GUI.cpp
    src/GUI/Sprite.cpp
)

add_executable(r-type ${SOURCES})

target_include_directories(r-type PRIVATE include)

target_link_libraries(r-type PRIVATE sfml-graphics sfml-window sfml-system sfml-audio)

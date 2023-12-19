##
## RType
##
## Root CMakeLists.txt
##

cmake_minimum_required(VERSION 3.8)

project(RType)
include(FetchContent)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

FetchContent_Declare(SFML GIT_REPOSITORY https://github.com/SFML/SFML.git GIT_TAG 2.5.1)
FetchContent_MakeAvailable(SFML)

include_directories(${CMAKE_SOURCE_DIR}/include)

set(SOURCES
    ${CMAKE_SOURCE_DIR}/src/Main.cpp

    ${CMAKE_SOURCE_DIR}/src/Core/Core.cpp
    ${CMAKE_SOURCE_DIR}/src/Core/Registry.cpp
    ${CMAKE_SOURCE_DIR}/src/Core/SparseArray.cpp

    ${CMAKE_SOURCE_DIR}/src/GUI/GUI.cpp
    ${CMAKE_SOURCE_DIR}/src/GUI/Sprite.cpp
)

add_executable(r-type ${SOURCES})


target_link_libraries(r-type sfml-graphics sfml-window sfml-system sfml-audio)
target_link_libraries(r-type pthread)

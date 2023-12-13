##
## RType
##
## Root CMakeLists.txt
##

cmake_minimum_required(VERSION 3.8)

project(RTypeServer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/include)

set(SOURCES
    ${CMAKE_SOURCE_DIR}/src/Main.cpp
    ${CMAKE_SOURCE_DIR}/src/ECS/ECS.cpp
    ${CMAKE_SOURCE_DIR}/src/ECS/Registry.cpp
    ${CMAKE_SOURCE_DIR}/src/ECS/SparseArray.cpp
    ${CMAKE_SOURCE_DIR}/src/ECS/SystemHandler.cpp
    ${CMAKE_SOURCE_DIR}/src/GUI/GUI.cpp
    ${CMAKE_SOURCE_DIR}/src/GUI/Sprite.cpp
    ${CMAKE_SOURCE_DIR}/src/Network/Server.cpp
    ${CMAKE_SOURCE_DIR}/src/Network/Client.cpp
)

add_executable(r-type-server ${SOURCES})

target_link_libraries(r-type-server sfml-graphics sfml-window sfml-system)
target_link_libraries(r-type-server pthread)

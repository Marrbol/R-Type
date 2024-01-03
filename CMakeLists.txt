##
## RType
##
## Root CMakeLists.txt
##

# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name
project(RType)
include(FetchContent)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

FetchContent_Declare(SFML GIT_REPOSITORY https://github.com/SFML/SFML.git GIT_TAG 2.6.0)
FetchContent_MakeAvailable(SFML)

include_directories(${CMAKE_SOURCE_DIR}/include)

set(SOURCES
    ${CMAKE_SOURCE_DIR}/src/Main.cpp

    src/Core/Core.cpp
    src/Core/Registry.cpp
    src/Core/SparseArray.cpp
    src/Core/SystemHandler.cpp

    src/GUI/GUI.cpp
)

# Create executable
add_executable(r-type ${SOURCES})

# Include directories
target_include_directories(r-type PRIVATE include)
target_include_directories(r-type PRIVATE lib)

# Add subdirectories
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/Physics)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/Render)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/Control)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/DestroyOutOfBounds)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/Collision)


# Link libraries
if (UNIX)
    target_link_libraries(r-type PRIVATE dl)
endif (UNIX)

target_link_libraries(r-type PRIVATE PhysicsModule)
target_link_libraries(r-type PRIVATE RenderModule)
target_link_libraries(r-type PRIVATE ControlModule)
target_link_libraries(r-type PRIVATE DestroyOutOfBoundsModule)
target_link_libraries(r-type PRIVATE CollisionModule)

target_link_libraries(r-type PRIVATE sfml-graphics)
target_link_libraries(r-type PRIVATE sfml-window)
target_link_libraries(r-type PRIVATE sfml-system)
target_link_libraries(r-type PRIVATE sfml-audio)

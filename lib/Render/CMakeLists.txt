##
## RType
##
## CMakeLists.txt
##

# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Minimum C++ standard required
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set the source files for the shared library
set(LIBRARY_SOURCES
    RenderModule.cpp
)

# Create the shared library
add_library(RenderModule STATIC ${LIBRARY_SOURCES})

# Specify include directories for the library
target_include_directories(RenderModule PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../include)

# Link SFML libraries from the root project
target_link_libraries(RenderModule PUBLIC sfml-graphics sfml-window sfml-system)
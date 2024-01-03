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

# Définissez les variables de chemin d'accès SFML
message(STATUS "not Found")
if(SFML_FOUND)
  message(STATUS "Found")
  set(SFML_LIBRARY_DIRS ${SFML_LIBRARY_DIRS})
  set(SFML_INCLUDE_DIRS ${SFML_INCLUDE_DIRS})
endif()

# Set the source files for the shared library
set(LIBRARY_SOURCES
    ControlModule.cpp
)

# Create the shared library
add_library(ControlModule STATIC ${LIBRARY_SOURCES})

# Specify include directories for the library
target_include_directories(ControlModule PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../include)

# Link SFML libraries from the root project
target_link_libraries(ControlModule PUBLIC sfml-graphics sfml-window sfml-system)
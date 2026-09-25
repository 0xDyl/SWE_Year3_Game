cmake_minimum_required(VERSION 3.10)
project(SWE_Year3_Game)

# Sorts my LSP
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Sets version to C++ 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output directory setup
set(OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})

# Add SFML submodule/source folder
add_subdirectory("lib/SFML")

# Practical 1 
add_executable(practical1 src/practical1.cpp)
target_link_libraries(practical1 PRIVATE sfml-graphics sfml-window sfml-system)

# Practical 2  -> Pong Practical
add_executable(pong src/practical2.cpp)
target_link_libraries(pong PRIVATE sfml-graphics sfml-window sfml-system)

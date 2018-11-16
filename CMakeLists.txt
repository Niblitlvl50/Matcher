
cmake_minimum_required(VERSION 3.6)

project(matcher)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)
# set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-long-long -pedantic -Wno-unused-parameter -Wno-unused-variable -Wno-format-pedantic")

add_subdirectory("Mono1/")
include_directories("Mono1/MonoEngine" "Mono1/third_party")

# Game
file(GLOB_RECURSE game_source_files "src/*.cpp")
add_executable(game ${game_source_files})
add_dependencies(game mono)
target_include_directories(game PRIVATE "src/")
target_link_libraries(game mono)

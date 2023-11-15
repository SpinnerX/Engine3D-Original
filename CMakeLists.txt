cmake_minimum_required(VERSION 3.15)
set(PROJECT_NAME GameEngine)
set(CMAKE_CXX_FLAGS "-Wno-dev")
set(CMAKE_CXX_FLAGS "-std=c++20")

project(${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 20)

find_package(Logger REQUIRED)

include_directories(
  ${PROJECT_SOURCE_DIR}/GameEngine/include
  ${PROJECT_SOURCE_DIR}/GameEngine/include/GameEngine
)

set(
  all_src
  GameEngine/src/GameEngine/core.cpp
  GameEngine/include/GameEngine/Application.cpp
)

add_subdirectory(Sandbox)

add_library(${PROJECT_NAME} STATIC ${all_src})
add_library(Engine::Engine ALIAS ${PROJECT_NAME}) # Allows to alias the library

set_property(TARGET ${PROJECT_NAME} PROPERTY INTERPROCEDURAL_OPTIMIZATION True)

# Linking the included directories
target_include_directories(
  ${PROJECT_NAME}
  PUBLIC
  ${PROJECT_SOURCE_DIR}/GameEngine/include
  ${PROJECT_SOURCE_DIR}/GameEngine/include/GameEngine
)

target_link_libraries(${PROJECT_NAME} Logger)
cmake_minimum_required(VERSION 3.15)
set(PROJECT_NAME GameEngine)
set(CMAKE_CXX_FLAGS "-Wno-dev")
set(CMAKE_CXX_FLAGS "-std=c++20")

project(${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 23)
include(cmake/precompiled_headers.cmake)

find_package(fmt REQUIRED)
find_package(spdlog REQUIRED)

include_directories(
  ${PROJECT_SOURCE_DIR}/GameEngine/include
  ${PROJECT_SOURCE_DIR}/GameEngine/include/GameEngine
)

set(
  all_src
  GameEngine/src/GameEngine/core.cpp
  GameEngine/include/GameEngine/Application.cpp
  GameEngine/include/GameEngine/EngineLogger.cpp
)

# Adding precompiled headers to speed up the compilation process
# add_precompiled_header(${PROJECT_NAME} Application.h FORCEINCLUDE SOURCE_CXX Application.cpp)
# add_precompiled_header(${PROJECT_NAME} EngineLogger.h FORCEINCLUDE SOURCE_CXX EngineLogger.cpp)
# add_precompiled_header(${PROJECT_NAME} EntryPoint.h)
# add_precompiled_header(${PROJECT_NAME} GameEngine.h)
# add_precompiled_header(${PROJECT_NAME} core.h)
add_precompiled_header(${PROJECT_NAME} include/GameEnginePrecompiledHeader.h FORCEINCLUDE SOURCE_CXX include/GameEnginePrecompiledHeader.cpp)


add_subdirectory(Sandbox)

add_library(${PROJECT_NAME} SHARED ${all_src})
add_library(Engine::Engine ALIAS ${PROJECT_NAME}) # Allows to alias the library

set_property(TARGET ${PROJECT_NAME} PROPERTY INTERPROCEDURAL_OPTIMIZATION True)

# Linking the included directories
target_include_directories(
  ${PROJECT_NAME}
  PUBLIC
  ${PROJECT_SOURCE_DIR}/GameEngine/include
  ${PROJECT_SOURCE_DIR}/GameEngine/include/GameEngine
)

# This is how you can have precompiled headers
# This allows for faster compile time
target_precompile_headers(${PROJECT_NAME} PRIVATE
  "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/GameEngine/include/GameEnginePrecompiledHeader.h>"
)

target_link_libraries(${PROJECT_NAME} fmt::fmt spdlog::spdlog)
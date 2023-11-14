cmake_minimum_required(VERSION 3.15)

set(PROJECT_NAME GameEngineTutorial)
project(${PROJECT_NAME} VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)

find_package(formatCpp REQUIRED)
find_package(Logger REQUIRED)

set(
    all_src
    main.cpp
)

add_executable(
    ${PROJECT_NAME}
    ${all_src}
)

target_link_libraries(
    ${PROJECT_NAME}
    formatCpp
    Logger
)
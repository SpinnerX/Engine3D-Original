# We are going to include cmake modules
message(STATUS "CMAKE_CURRENT_SOURCE DIR =======> ${CMAKE_CURRENT_SOURCE_DIR}")
# include(${CMAKE_CURRENT_SOURCE_DIR})
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/unix/libs/glfw.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/unix/libs/fmt.cmake)
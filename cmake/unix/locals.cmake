# This will be calling cmake modules that are locally in our "/usr/local/include" directory
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/unix/locals/imgui.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/unix/locals/glad.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/unix/locals/stbi_image.cmake)
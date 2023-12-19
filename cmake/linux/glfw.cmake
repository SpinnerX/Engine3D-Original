# Linux GLFW cmake module
# NOTE: On Linux if you didnt mess with the default
# The default filepath is /usr/lib/x86_64-linux-gnu/cmake/... -> <-
# Linux Installation commands found here: https://medium.com/geekculture/a-beginners-guide-to-setup-opengl-in-linux-debian-2bfe02ccd1e
message(STATUS "Linux loading opengl")

set(glfw3_DIR /usr/lib/x86_64-linux-gnu/cmake/glfw3)

if(NOT EXISTS ${glfw3_DIR})
    message(SEND_ERROR "Could not load GLFW cmake directory")
    message(SEND_ERROR "Could not load ${glfw3_DIR}")
endif()

find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)


target_link_libraries(
    ${PROJECT_NAME}
    glfw
    OpenGL::GL
)
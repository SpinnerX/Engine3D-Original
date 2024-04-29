cmake_minimum_required (VERSION 3.15)

set(PROJECT_NAME Sandbox-Internal)

set(CMAKE_CXX_STANDARD 20)
if(UNIX)
add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)
endif(UNIX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "") # works (in creating the compile_commands.json file)
project(${PROJECT_NAME})

include_directories(
    ../
)

#find_package(Engine3D REQUIRED)
#find_package(glfw3 REQUIRED)
#find_package(OpenGL REQUIRED)
#find_package(GLEW REQUIRED)
#find_package(GLUT REQUIRED)
#find_package(imgui REQUIRED)
#find_package(ImGuizmo REQUIRED)
## find_package(Vulkan REQUIRED)
#
#find_package(fmt REQUIRED)
#find_package(spdlog REQUIRED)
#find_package(glad REQUIRED)
#find_package(glm REQUIRED)
#find_package(box2d REQUIRED)
#find_package(yaml-cpp REQUIRED)


# Create the executable
add_executable(${PROJECT_NAME} Application.cpp)

#target_link_libraries(
#    ${PROJECT_NAME}
#	Engine3D::Engine3D
#)
target_link_libraries(${PROJECT_NAME}
		Engine3D
		${OPENGL_LIBRARIES}
		glfw
		${Vulkan_LIBRARIES}
		fmt::fmt
		spdlog::spdlog
		glm::glm
		tobanteGaming::Box2D
		yaml-cpp::yaml-cpp
		imgui
		glad
)
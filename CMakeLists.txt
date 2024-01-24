cmake_minimum_required(VERSION 3.15)
set(PROJECT_NAME GameEngine)

project(${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-std=c++20 -fsanitize=address")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "") # works (in creating the compile_commands.json file)

add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)

set(CMAKE_BUILT_TYPE Debug)
# set(THREADS_PREFER_PTHREAD_FLAG ON)

include(cmake/precompiled_headers.cmake)
include(cmake/modules/glad.cmake)
include(cmake/modules/imgui.cmake)
include(cmake/modules/stbi_image.cmake)

set(
  all_src
  GameEngine/src/GameEngine/core.cpp
  GameEngine/include/GameEngine/Core/Application.cpp
  GameEngine/include/GameEngine/Core/EngineLogger.cpp
  GameEngine/src/GameEngine/platforms/WindowsWindow.cpp
  GameEngine/include/GameEngine/Core/Layer.cpp
  GameEngine/include/GameEngine/Core/LayerStack.cpp
  ${imgui_src}
  ${glad_src}

  GameEngine/include/GameEngine/Imgui/ImGuiLayer.cpp

  GameEngine/include/GameEngine/platforms/OpenGL/OpenGLContext.cpp
  GameEngine/include/GameEngine/Renderer/Shader.cpp
  GameEngine/include/GameEngine/Renderer/Buffer.cpp
  GameEngine/include/GameEngine/platforms/OpenGL/OpenGLBuffer.cpp
  GameEngine/include/GameEngine/Renderer/Renderer.cpp
  GameEngine/include/GameEngine/Renderer/VertexArray.cpp
  GameEngine/include/GameEngine/platforms/OpenGL/OpenGLVertexArray.cpp
  GameEngine/include/GameEngine/Renderer/RendererAPI.cpp
  GameEngine/include/GameEngine/Renderer/RendererCommand.cpp
  GameEngine/include/GameEngine/platforms/OpenGL/OpenGLRendererAPI.cpp
  GameEngine/include/GameEngine/Renderer/OrthographicCamera.cpp
  GameEngine/include/GameEngine/platforms/OpenGL/OpenGLShader.cpp
  GameEngine/include/GameEngine/Renderer/Texture.cpp
  GameEngine/include/GameEngine/platforms/OpenGL/OpenGLTexture.cpp
  GameEngine/include/GameEngine/Renderer/OrthographicCameraController.cpp
  
  GameEngine/src/GameEngine/platforms/WindowsInput.cpp
  GameEngine/include/GameEngine/Renderer/Renderer2D.h
  GameEngine/include/GameEngine/Renderer/Renderer2D.cpp
  GameEngine/include/GameEngine/Renderer/SubTexture2D.cpp
  GameEngine/include/GameEngine/Renderer/Framebuffer.cpp
  GameEngine/include/GameEngine/platforms/OpenGL/OpenGLFramebuffer.cpp
  GameEngine/include/GameEngine/Scene/Scene.cpp
  GameEngine/include/GameEngine/Scene/Entity.cpp
  GameEngine/include/GameEngine/Scene/SceneCamera.cpp
  GameEngine/include/GameEngine/Scene/SceneSerializer.cpp
  ${stbi_src}
)

add_subdirectory(Sandbox)
add_subdirectory(RocketGame)
add_subdirectory(2DGameParticles)
add_subdirectory(GameEngine-Editor)

add_library(${PROJECT_NAME} SHARED ${all_src})
add_library(Engine::Engine ALIAS ${PROJECT_NAME}) # Allows to alias the library

# if(APPLE)
#   # add_precompiled_header(${PROJECT_NAME} include/GameEnginePrecompiledHeader.h FORCEINCLUDE SOURCE_CXX src/GameEnginePrecompiledHeader.cpp)
#   set_property(TARGET ${PROJECT_NAME} PROPERTY INTERPROCEDURAL_OPTIMIZATION True)
# endif(APPLE)

# Linking the included directories
target_include_directories(
  ${PROJECT_NAME}
  PUBLIC
  ${PROJECT_SOURCE_DIR}/GameEngine/include
  ${PROJECT_SOURCE_DIR}/GameEngine/include/GameEngine
  ${imgui_include}
  ${glad_include}
)

file(COPY Sandbox/assets DESTINATION ${CMAKE_BINARY_DIR}/Sandbox/assets)
file(COPY GameEngine-Editor/assets DESTINATION ${CMAKE_BINARY_DIR}/GameEngine-Editor/assets)

target_precompile_headers(${PROJECT_NAME} PUBLIC
  "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/GameEngine/include/GameEnginePrecompiledHeader.h>"
)


include(cmake/glfw.cmake)
include(cmake/yaml.cmake)
include(cmake/fmt.cmake)


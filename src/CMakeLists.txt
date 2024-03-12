include_directories(
	Engine3D
	../
)

set(
	INCLUDE_DIR
	Engine3D	
)

# set(
# 	all_src
# 	Engine3D/Core/core.cpp
# 	Engine3D/Core/Application.cpp
# 	Engine3D/Core/EntryPoint.cpp
# 	Engine3D/Core/EngineLogger.cpp
# 	Engine3D/OpenGL/OpenGLWindow.cpp
# 	Engine3D/Core/Layer.cpp
# 	Engine3D/Core/LayerStack.cpp
# 	Engine3D/Events/InputPoll.cpp
# 	Engine3D/OpenGL/OpenGLInputPoll.cpp
# 	Engine3D/interfaces/Buffer.cpp
# 	Engine3D/interfaces/RendererAPI.cpp
# 	Engine3D/interfaces/Shader.cpp

# 	Engine3D/OpenGL/OpenGLBuffer.cpp
# 	Engine3D/OpenGL/OpenGLShader.cpp
# )

# set(
# 	all_headers
# 	../${INCLUDE_DIR}/Core/core.h
# 	../${INCLUDE_DIR}/Core/Application.h
# 	../${INCLUDE_DIR}/Core/EntryPoint.h
# 	../${INCLUDE_DIR}/Core/EngineLogger.h
# 	../${INCLUDE_DIR}/Events/Event.h
# 	../${INCLUDE_DIR}/Events/KeyEvent.h
# 	../${INCLUDE_DIR}/Events/KeyCodes.h
# 	../${INCLUDE_DIR}/Events/MouseEvent.h
# 	../${INCLUDE_DIR}/Events/MouseButtonCodes.h
# 	../${INCLUDE_DIR}/Events/ApplicationEvent.h
# 	../${INCLUDE_DIR}/OpenGL/OpenGLWindow.h
# 	../${INCLUDE_DIR}/Events/InputPoll.h
# 	../${INCLUDE_DIR}/OpenGL/OpenGLInputPoll.h
# 	../${INCLUDE_DIR}/interfaces/Buffer.h
# 	../${INCLUDE_DIR}/interfaces/RendererAPI.h
# 	../${INCLUDE_DIR}/interfaces/GraphicsContext.h

# 	../${INCLUDE_DIR}/OpenGL/OpenGLBuffer.h
# 	../${INCLUDE_DIR}/OpenGL/OpenGLShader.h
# )

set(
  all_src


  Engine3D/Core/EntryPoint.cpp
  Engine3D/Core/Application.cpp
  Engine3D/Core/EngineLogger.cpp
  Engine3D/Events/InputPoll.cpp
  Engine3D/Core/Layer.cpp
  Engine3D/Core/LayerStack.cpp

  Engine3D/ImGui/ImGuiLayer.cpp

  Engine3D/OpenGL/OpenGLContext.cpp
  Engine3D/interfaces/Shader.cpp
  Engine3D/interfaces/Buffer.cpp
  Engine3D/OpenGL/OpenGLBuffer.cpp
  Engine3D/Renderer/Renderer.cpp
  Engine3D/interfaces/VertexArray.cpp
  Engine3D/OpenGL/OpenGLVertexArray.cpp
  Engine3D/interfaces/RendererAPI.cpp
  Engine3D/Renderer/RendererCommand.cpp
  Engine3D/OpenGL/OpenGLRendererAPI.cpp
  Engine3D/Renderer/OrthographicCamera.cpp
  Engine3D/OpenGL/OpenGLShader.cpp
  Engine3D/interfaces/Texture.cpp
  Engine3D/OpenGL/OpenGLTexture.cpp
  Engine3D/Renderer/OrthographicCameraController.cpp

  Engine3D/OpenGL/OpenGLInputPoll.cpp
  
  Engine3D/OpenGL/OpenGLWindow.cpp
  Engine3D/Renderer/Renderer2D.cpp
  Engine3D/interfaces/SubTexture2D.cpp
  Engine3D/interfaces/Framebuffer.cpp
  Engine3D/OpenGL/OpenGLFramebuffer.cpp
  Engine3D/Scene/Scene.cpp
  Engine3D/Scene/Entity.cpp
  Engine3D/Scene/SceneCamera.cpp
  Engine3D/Scene/SceneSerializer.cpp
  Engine3D/image/stb_image.cpp

  Engine3D/platforms/Mac/MacPlatformUtils.cpp
  Engine3D/Math/Math.cpp
  Engine3D/Renderer/EditorCamera.cpp
  Engine3D/interfaces/UniformBuffer.cpp
  Engine3D/OpenGL/OpenGLUniformBuffer.cpp
)

# For Mac, linking AppKit only and only needing nfd_cocoa.m
if(APPLE)
  # For setting the filter list, macOS introduced allowedContentTypes in version 11.0 and deprecated allowedFileTypes in 12.0.
  # By default (set to ON), NFDe will use allowedContentTypes when targeting macOS >= 11.0.
  # Set this option to OFF to always use allowedFileTypes regardless of the target macOS version.
  # This is mainly needed for applications that are built on macOS >= 11.0 but should be able to run on lower versions
  # and should not be used otherwise.
  option(NFD_USE_ALLOWEDCONTENTTYPES_IF_AVAILABLE "Use allowedContentTypes for filter lists on macOS >= 11.0" ON)

  find_library(APPKIT_LIBRARY AppKit)
  if(NFD_USE_ALLOWEDCONTENTTYPES_IF_AVAILABLE)
    include(CheckCXXSourceCompiles)
    check_cxx_source_compiles(
      "
      #include <Availability.h>
      #if !defined(__MAC_OS_X_VERSION_MIN_REQUIRED) || !defined(__MAC_11_0) || __MAC_OS_X_VERSION_MIN_REQUIRED < __MAC_11_0
      static_assert(false);
      #endif
      int main() { return 0; }
      "
      NFD_USE_ALLOWEDCONTENTTYPES
    )
    if(NFD_USE_ALLOWEDCONTENTTYPES)
      find_library(UNIFORMTYPEIDENTIFIERS_LIBRARY UniformTypeIdentifiers)
      if(NOT UNIFORMTYPEIDENTIFIERS_LIBRARY)
        message(FATAL_ERROR "UniformTypeIdentifiers framework is not available even though we are targeting macOS >= 11.0")
      endif()
    endif()
  endif()
  list(APPEND all_src Engine3D/platforms/Mac/nfd_cocoa.m)
endif()

set(
  all_headers
  ../${INCLUDE_DIR}/Core/Application.h
  ../${INCLUDE_DIR}/Core/core.h
  ../${INCLUDE_DIR}/Core/EngineLogger.h
  ../${INCLUDE_DIR}/Core/EntryPoint.h
#   ../${INCLUDE_DIR}/Core/GameEngine.h
  ../${INCLUDE_DIR}/Events/InputPoll.h
  ../${INCLUDE_DIR}/Core/Window.h
  ../${INCLUDE_DIR}/Core/Layer.h
  ../${INCLUDE_DIR}/Core/LayerStack.h
  ../${INCLUDE_DIR}/Core/Timer.h
  ../${INCLUDE_DIR}/Core/Timestep.h
  ../${INCLUDE_DIR}/Entt/entt.h
  ../${INCLUDE_DIR}/Imgui/ImGuiLayer.h

  ../${INCLUDE_DIR}/OpenGL/OpenGLContext.h
  ../${INCLUDE_DIR}/interfaces/Shader.h
  ../${INCLUDE_DIR}/interfaces/Buffer.h
  ../${INCLUDE_DIR}/OpenGL/OpenGLBuffer.h
  ../${INCLUDE_DIR}/Renderer/Renderer.h
  ../${INCLUDE_DIR}/interfaces/VertexArray.h
  ../${INCLUDE_DIR}/OpenGL/OpenGLVertexArray.h
  ../${INCLUDE_DIR}/interfaces/RendererAPI.h
  ../${INCLUDE_DIR}/Renderer/RenderCommand.h
  ../${INCLUDE_DIR}/OpenGL/OpenGLRendererAPI.h
  ../${INCLUDE_DIR}/Renderer/OrthographicCamera.h
  ../${INCLUDE_DIR}/OpenGL/OpenGLShader.h
  ../${INCLUDE_DIR}/interfaces/Texture.h
  ../${INCLUDE_DIR}/OpenGL/OpenGLTexture.h
  ../${INCLUDE_DIR}/Renderer/OrthographicCameraController.h

  ../${INCLUDE_DIR}/platforms/PlatformUtils.h

  ../${INCLUDE_DIR}/Events/ApplicationEvent.h
  ../${INCLUDE_DIR}/Events/Event.h
  ../${INCLUDE_DIR}/Events/KeyEvent.h
  ../${INCLUDE_DIR}/Events/MouseEvent.h
  ../${INCLUDE_DIR}/OpenGL/OpenGLInputPoll.h
  ../${INCLUDE_DIR}/image/stb_image.h

  ../${INCLUDE_DIR}/platforms/Mac/nfd.h
  ../${INCLUDE_DIR}/platforms/Mac/nfd.hpp
)

# if(UNIX AND NOT APPLE)
find_package(glfw3 REQUIRED)
# endif(UNIX AND NOT APPLE)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
# find_package(GLUT REQUIRED)

find_package(imgui REQUIRED)
find_package(ImGuizmo REQUIRED)
# find_package(Vulkan REQUIRED)

find_package(fmt REQUIRED)
find_package(spdlog REQUIRED)
find_package(glad REQUIRED)
find_package(glm REQUIRED)

add_library( ${PROJECT_NAME} ${all_src} ${all_headers} )

# NOTE: Using {OPENGL_gl_LIBRARY}, if compiling on Apple.

if(UNIX AND NOT APPLE)
	target_link_libraries(
		${PROJECT_NAME}
		glfw
		# ${OPENGL_gl_LIBRARY}
		OpenGL::GL
		Vulkan::Vulkan
		imgui::imgui
		fmt::fmt
		glm::glm
		spdlog::spdlog
		glad::glad
	)
endif(UNIX AND NOT APPLE)

if(APPLE)
target_link_libraries(
	${PROJECT_NAME}
	glfw
	imgui::imgui
	ImGuizmo::ImGuizmo
	fmt::fmt
	glm::glm
	spdlog::spdlog
	glad::glad
	GLEW::GLEW
)
endif(APPLE)

target_include_directories(${PROJECT_NAME}
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../${INCLUDE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)


set_target_properties(${PROJECT_NAME} PROPERTIES
	CXX_STANDARD 20
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
)

if(MSVC)
	set_target_properties(${PROJECT_NAME} PROPERTIES
    COMPILE_PDB_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
	COMPILE_PDB_NAME ${PROJECT_NAME}
  )

  install(
	  FILES "${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/${PROJECT_NAME}.pdb"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
    OPTIONAL
  )
endif()

if (BUILD_SHARED_LIBS)
	target_compile_definitions(${PROJECT_NAME}
    PUBLIC
	${PROJECT_NAME}_SHARED
  )
endif()

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" PREFIX "src" FILES ${all_src})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/../${INCLUDE_DIR}" PREFIX "include" FILES ${all_headers})

install(
	TARGETS ${PROJECT_NAME}
	EXPORT ${PROJECT_NAME}Config
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(
	EXPORT ${PROJECT_NAME}Config
	NAMESPACE Engine3D::
	DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
)

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
	"${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
  COMPATIBILITY SameMajorVersion
)

install(
	FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
	DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
)

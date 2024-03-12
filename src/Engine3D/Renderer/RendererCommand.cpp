#include <Engine3D/Engine3DPrecompiledHeader.h>
#include <Engine3D/Renderer/RenderCommand.h>
#include <OpenGL/OpenGLRendererAPI.h> // OpenGL draw calls are going to be implemented

namespace Engine3D{
    Scope<RendererAPI> RendererCommand::_rendererAPI = CreateScope<OpenGLRendererAPI>();
};

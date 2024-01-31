#include <GameEnginePrecompiledHeader.h>
#include <GameEngine/Renderer/Framebuffer.h>
#include <GameEngine/Renderer/Renderer.h>
#include <GameEngine/platforms/OpenGL/OpenGLFramebuffer.h>
/* #include <GameEngine/platforms/OpenGL/OpenGLFramebuffe_Experiemental.h> */

namespace RendererEngine {
	Ref<FrameBuffer> FrameBuffer::Create(const FrameBufferSpecifications &specs){
		switch (Renderer::getAPI()) {
			case RendererAPI::API::None: render_core_assert(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL: return CreateRef<OpenGLFrameBuffer>(specs);
		}

		render_core_assert(false, "Unknown RendererAPI!");
		return nullptr;
	}
}

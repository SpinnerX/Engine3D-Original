#include <GameEngine/Renderer/UniformBuffer.h>
#include <GameEngine/Renderer/Renderer.h>

namespace RendererEngine{
	Ref<UniformBuffer> UniformBuffer::create(uint32_t size, uint32_t binding){
		switch (Renderer::getAPI()) {
			case RendererEngine::RendererAPI::API::None: assert(false);
			case RendererEngine::RendererAPI::API::OpenGL: break;
			default:
				assert(false);
		}
		return nullptr;
	}
};

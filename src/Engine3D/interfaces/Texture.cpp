#include <Engine3D/Engine3DPrecompiledHeader.h>
#include <Engine3D/interfaces/Texture.h>
#include <Engine3D/Renderer/Renderer.h>
#include <OpenGL/OpenGLTexture.h>

namespace Engine3D{

    Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height){
		switch (Renderer::getAPI()) {
			case RendererAPI::API::None:
				render_assert(false, "RendererAPI::None is currently not supported!");
				return nullptr;
			case RendererAPI::API::OpenGL:
				return CreateRef<OpenGLTexture2D>(width, height);
		}
	}

    Ref<Texture2D> Texture2D::Create(const std::string& filepath){
        switch (RendererAPI::getAPI()){
        case RendererAPI::API::None:
            render_core_assert(false, "RenderAPI::None is currently not supported!");
            return nullptr;
        case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLTexture2D>(filepath);
        }

        render_core_assert(false, "Unknown renderer API");
        return nullptr;
    }
};

#include <GameEnginePrecompiledHeader.h>
#include <GameEngine/Renderer/Texture.h>
#include <GameEngine/Renderer/Renderer.h>
#include <GameEngine/platforms/OpenGL/OpenGLTexture.h>

namespace RendererEngine{
    Ref<Texture2D> Texture2D::Create(const std::string& filepath){
        switch (RendererAPI::getAPI()){
        case RendererAPI::API::None:
            render_core_assert(false, "RenderAPI::None is currently not supported!");
            return nullptr;
        case RendererAPI::API::OpenGL:
            return std::make_shared<OpenGLTexture2D>(filepath);
        }

        render_core_assert(false, "Unknown renderer API");
        return nullptr;
    }
};
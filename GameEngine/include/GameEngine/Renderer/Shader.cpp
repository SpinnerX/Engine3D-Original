#include <GameEnginePrecompiledHeader.h>
#include <GameEngine/Renderer/Shader.h>
#include <GameEngine/Renderer/Renderer.h>
#include <GameEngine/platforms/OpenGL/OpenGLShader.h>

namespace RendererEngine{

    Shader* Shader::CreateShader(const std::string& filepath){
        switch (RendererAPI::getAPI()){
            case RendererAPI::API::None:
                render_core_assert(false, "RenderAPI::None is currently not supported!");
                return nullptr;
            case RendererAPI::API::OpenGL: return new OpenGLShader(filepath);
        }

        render_core_assert(false, "Unknown renderer API");
        return nullptr;
    }

    // This is what allows us to create different platform specific shaders
    Shader* Shader::CreateShader(const std::string& vertexSrc, const std::string& fragmentSrc){
        switch (RendererAPI::getAPI()){
            case RendererAPI::API::None:
                render_core_assert(false, "RenderAPI::None is currently not supported!");
                return nullptr;
            case RendererAPI::API::OpenGL:
                return new OpenGLShader(vertexSrc, fragmentSrc);
        }

        render_core_assert(false, "Unknown renderer API");
        return nullptr;
    }
};
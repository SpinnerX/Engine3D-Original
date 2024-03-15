#include <Engine3D/Engine3DPrecompiledHeader.h>
#include <Engine3D/interfaces/Shader.h>
#include <Engine3D/Renderer2D/Renderer.h>
#include <OpenGL/OpenGLShader.h>

namespace Engine3D{

    Ref<Shader> Shader::CreateShader(const std::string& filepath){
        switch (RendererAPI::getAPI()){
            case RendererAPI::API::None:
                render_core_assert(false, "RenderAPI::None is currently not supported!");
                return nullptr;
            case RendererAPI::API::OpenGL: return CreateRef<OpenGLShader>(filepath);
        }

        render_core_assert(false, "Unknown renderer API");
        return nullptr;
    }

    // This is what allows us to create different platform specific shaders
    Ref<Shader> Shader::CreateShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc){
        switch (RendererAPI::getAPI()){
            case RendererAPI::API::None:
                render_core_assert(false, "RenderAPI::None is currently not supported!");
                return nullptr;
            case RendererAPI::API::OpenGL:
                return CreateRef<OpenGLShader>(name, vertexSrc, fragmentSrc);
        }

        render_core_assert(false, "Unknown renderer API");
        return nullptr;
    }

    //////////////////////
    /// Shader Library ///
    //////////////////////

    void ShaderLibrary::add(const Ref<Shader>& shader){
        auto& name = shader->getName();
        if(exists(name)) coreLogError("Shader already exists");
        _shaders[name] = shader;
    }

    void ShaderLibrary::add(const std::string& name, const Ref<Shader>& shader){
        if(exists(name)) coreLogError("Shader aready exists");

        _shaders[name] = shader;
    }

    Ref<Shader> ShaderLibrary::load(const std::string& filepath){
        auto shader = Shader::CreateShader(filepath);
        add(shader);
        return shader;
    }

    void ShaderLibrary::load(const std::string& name, const std::string& filepath){
        auto shader = Shader::CreateShader(filepath);
        add(name, shader);
    }

    Ref<Shader>& ShaderLibrary::get(const std::string& name){
        if(!exists(name)){
            coreLogError("Shader not found");
        }

        return _shaders[name];
    }

    bool ShaderLibrary::exists(const std::string& name){
        return _shaders.contains(name);
    }
};

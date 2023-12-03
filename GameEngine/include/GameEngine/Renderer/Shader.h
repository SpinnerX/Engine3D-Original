#pragma once
#include <string>
#include <glm/glm.hpp>
namespace RendererEngine{

    // Creating a Shader class
    // Eventually we are creating a renderer where other Renderer API's can customize and use these functions
    // - basically be implemented per API
    class Shader{
    public:
        virtual ~Shader() = default;

        virtual void bind() const = 0;

        virtual void unbind() const = 0;

        static Shader* CreateShader(const std::string& path);
        static Shader* CreateShader(const std::string& vertexSrc, const std::string& fragmentSrc);

    private:
        uint32_t _rendererID; // Keeping track uniquely identifying this object
        // static int counter;
    };
};
#pragma once
#include <GameEngine/Renderer/Shader.h>


namespace RendererEngine{
    // Shader class (Specific to OpenGL)
    // Eventually we are creating a renderer where other Renderer API's can customize and use these functions
    // - basically be implemented per API
    class OpenGLShader : public Shader{
    public:
        // In the future we should take these in as a file.
        OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
        ~OpenGLShader();

        virtual void bind() const override;

        virtual void unbind() const override;

        void uploadUniformInt(const std::string& name, int values);
        void uploadUniformFloat(const std::string& name, float values);
        void uploadUniformFloat2(const std::string& name, const glm::vec2& values);
        void uploadUniformFloat3(const std::string& name, const glm::vec3& values);
        void uploadUniformFloat4(const std::string& name, const glm::vec4& values);

        void uploadUniformMat3(const std::string& name, const glm::mat3& matrix);
        void uploadUniformMat4(const std::string& name, const glm::mat4& matrix);
    private:
        uint32_t _rendererID; // Keeping track uniquely identifying this object
        // static int counter;
    };
};
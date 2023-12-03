#include <GameEnginePrecompiledHeader.h>
#include <GameEngine/platforms/OpenGL/OpenGLRendererAPI.h>
#include <glad/glad.h>

namespace RendererEngine{
    void OpenGLRendererAPI::init() {
        // What allows for testing
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void OpenGLRendererAPI::setClearColor(const glm::vec4& color) {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void OpenGLRendererAPI::clear() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLRendererAPI::drawIndexed(const Ref<VertexArray>& vertexArr) {
        glDrawElements(GL_TRIANGLES, vertexArr->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
    }

};
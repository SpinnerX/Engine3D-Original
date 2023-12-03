#pragma once
#include <GameEngine/Renderer/RenderCommand.h>
#include <GameEngine/Renderer/OrthographicCamera.h>
#include <GameEngine/Renderer/Shader.h>

namespace RendererEngine{
    
    // Renderer
    // - The renderer is what allows for bind and unbinding
    // - Only Renderer abstracts away the bind and unbinding functions.
    class Renderer{
    public:

        // Used to initialize our renderer
        // Initialing our renderer command, as well
        static void init();

        static void beginScene(OrthographicCamera& camera);

        static void endScene();

        // Submitted into a renderer queue
        // Then is evaluated probably in a different thread and will get rendered
        // Adding transform
        static void submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

        inline static RendererAPI::API getAPI() { return RendererAPI::getAPI(); }

    private:
        struct SceneData{
            glm::mat4 viewProjectionMatrix;
        };

        static SceneData* _sceneData;

    };
};
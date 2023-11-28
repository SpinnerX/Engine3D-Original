#include <GameEnginePrecompiledHeader.h>
#include <GameEngine/Renderer/Renderer.h>

namespace RendererEngine{
    Renderer::SceneData* Renderer::_sceneData = new Renderer::SceneData;

    void Renderer::beginScene(OrthographicCamera& camera){
        _sceneData->viewProjectionMatrix = camera.getViewProjectionMatrix();
    }

    void Renderer::endScene(){

    }

    void Renderer::submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform){
        shader->bind();
        shader->uploadUniformMat4("u_ViewProjection", _sceneData->viewProjectionMatrix);
        shader->uploadUniformMat4("u_Transform", transform); // whenever we submit, def need to do this per object

        vertexArray->bind();
        RendererCommand::drawIndexed(vertexArray);
    }
};
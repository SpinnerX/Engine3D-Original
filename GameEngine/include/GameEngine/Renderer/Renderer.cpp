#include <GameEnginePrecompiledHeader.h>
#include <GameEngine/Renderer/Renderer.h>
#include <GameEngine/platforms/OpenGL/OpenGLShader.h>
#include <memory>

namespace RendererEngine{
    Renderer::SceneData* Renderer::_sceneData = new Renderer::SceneData;

    void Renderer::init(){
        RendererCommand::init();
    }
	
	void Renderer::onWindowResize(uint32_t w, uint32_t h){
		
	}

    void Renderer::beginScene(OrthographicCamera& camera){
        _sceneData->viewProjectionMatrix = camera.getViewProjectionMatrix();
    }

    void Renderer::endScene(){

    }

    void Renderer::submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform){
        shader->bind();
        std::dynamic_pointer_cast<OpenGLShader>(shader)->uploadUniformMat4("u_ViewProjection", _sceneData->viewProjectionMatrix);
        std::dynamic_pointer_cast<OpenGLShader>(shader)->uploadUniformMat4("u_Transform", transform); // whenever we submit, def need to do this per object

        vertexArray->bind();
        RendererCommand::drawIndexed(vertexArray);
    }
};

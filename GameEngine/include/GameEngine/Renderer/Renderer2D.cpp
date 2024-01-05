#include "Renderer/Buffer.h"
#include "Renderer/Texture.h"
#include <GameEnginePrecompiledHeader.h>
#include <GameEngine/Renderer/Renderer2D.h>
#include <GameEngine/Renderer/VertexArray.h>
#include <GameEngine/Renderer/RenderCommand.h>
#include <GameEngine/platforms/OpenGL/OpenGLShader.h>
#include <glm/gtc/matrix_transform.hpp>

namespace RendererEngine{

	// This data wont get deleted unless we delete this manually.
	struct Renderer2DStorage{
		Ref<VertexArray> quadVertexArray;
		Ref<Shader> flatColorShader;
		Ref<Shader> textureShader;
	};

	static Renderer2DStorage* _data; // So this could be unique to this translation unit

	void Renderer2D::Init(){
		_data = new Renderer2DStorage();
		_data->quadVertexArray = VertexArray::Create();

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Ref<VertexBuffer> squareVB;
		squareVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		
		squareVB->setLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float2, "a_TexCoord" }
		});

		_data->quadVertexArray->addVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Ref<IndexBuffer> squareIB;
		squareIB.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		_data->quadVertexArray->setIndexBuffer(squareIB);

		/* _flatColorShader = Shader::Create("assets/shaders/FlatColor.glsl"); */
		_data->flatColorShader = Shader::CreateShader("assets/sandbox2DShaders/FlatColor.glsl");
		_data->textureShader = Shader::CreateShader("assets/shaders/texture.glsl");
		_data->textureShader->setInt("u_Texture", 0);
	}

	void Renderer2D::Shutdown(){
		delete _data; // dont want to automatically delete this (ref to using smart ptrs), because we want them deleted when the 2D renderer shuts down.
	}

	void Renderer2D::beginScene(const OrthographicCamera& camera){

		// Simply uploads the camera data
		// upload is more API specific (actual OpenGL to set that uniform)
		// Where set is just set is a much higher level concept.
		_data->flatColorShader->bind();
		_data->flatColorShader->setMat4("u_ViewProjection", camera.getViewProjectionMatrix());
		_data->textureShader->bind();
		_data->textureShader->setMat4("u_ViewProjection", camera.getViewProjectionMatrix());
	}

	void Renderer2D::endScene(){

	}

	void Renderer2D::drawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color){
		drawQuad({pos.x, pos.y, 0.0f}, size, color);
	}
	
	void Renderer2D::drawQuad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color){
		_data->flatColorShader->bind();
		_data->flatColorShader->setFloat4("u_Color", color);
		
		// This is how we are going to do transformation
		// Since we aren't doing rotation, we are handling Translation(position) and Scale (size)
		// Whereas mat4(1.0f) is going to be our identity matrix
		// Uncomment this to see to see the effect of rotation...
		/* glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * glm::rotate(glm::mat4(1.0f), 180.0f, pos) * */
		/* 					  glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f}); */
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) *
							  glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});

		_data->flatColorShader->setMat4("u_Transform", transform);

		// Actual draw call
		_data->quadVertexArray->bind();
		RendererCommand::drawIndexed(_data->quadVertexArray);
	}
	
	void Renderer2D::drawQuad(const glm::vec2& pos, const glm::vec2& size, const Ref<Texture2D>& texture){
		drawQuad({pos.x, pos.y, 0.0f}, size, texture);
	}

	void Renderer2D::drawQuad(const glm::vec3& pos, const glm::vec2& size, const Ref<Texture2D>& texture){
		// This is how we are going to be drawing the texture onto the objects
		// - By first binding that texture, then when we bind that texture to that shader.
		_data->textureShader->bind();
		
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});
		
		texture->bind();
		_data->textureShader->setMat4("u_Transform", transform);

		// Actual draw call
		_data->quadVertexArray->bind();
		RendererCommand::drawIndexed(_data->quadVertexArray);
	}
	
};

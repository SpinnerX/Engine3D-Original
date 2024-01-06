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
		Ref<Shader> textureShader;
		Ref<Texture2D> whiteTexture;
	};

	static Renderer2DStorage* _data; // So this could be unique to this translation unit

	void Renderer2D::Init(){
		RENDER_PROFILE_FUNCTION();

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
		
		_data->whiteTexture = Texture2D::Create(1,1);
		uint32_t whiteTextureData = 0xffffffff; // four f's for every channel
		_data->whiteTexture->setData(&whiteTextureData, sizeof(uint32_t));

		_data->textureShader = Shader::CreateShader("assets/shaders/texture.glsl");
		_data->textureShader->setInt("u_Texture", 0);
	}

	void Renderer2D::Shutdown(){
		RENDER_PROFILE_FUNCTION();
		delete _data; // dont want to automatically delete this (ref to using smart ptrs), because we want them deleted when the 2D renderer shuts down.
	}

	void Renderer2D::beginScene(const OrthographicCamera& camera){
		RENDER_PROFILE_FUNCTION();

		// Simply uploads the camera data
		// upload is more API specific (actual OpenGL to set that uniform)
		// Where set is just set is a much higher level concept.
		_data->textureShader->bind();
		_data->textureShader->setMat4("u_ViewProjection", camera.getViewProjectionMatrix());
	}

	void Renderer2D::endScene(){

	}

	void Renderer2D::drawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color){
		drawQuad({pos.x, pos.y, 0.0f}, size, color);
	}
	
	void Renderer2D::drawQuad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color){
		RENDER_PROFILE_FUNCTION();
		_data->textureShader->setFloat4("u_Color", color);
		_data->textureShader->setFloat("u_TilingFactor", 1.0f);

		// Bind white texture here
		_data->whiteTexture->bind();
		
		// This is how we are going to do transformation
		// Since we aren't doing rotation, we are handling Translation(position) and Scale (size)
		// Whereas mat4(1.0f) is going to be our identity matrix
		// Uncomment this to see to see the effect of rotation...
		/* glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * glm::rotate(glm::mat4(1.0f), 180.0f, pos) * */
		/* 					  glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f}); */
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) *
							  glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});

		_data->textureShader->setMat4("u_Transform", transform);

		_data->quadVertexArray->bind();
		RendererCommand::drawIndexed(_data->quadVertexArray);
	}
	
	void Renderer2D::drawQuad(const glm::vec2& pos, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor){
		drawQuad({pos.x, pos.y, 0.0f}, size, texture, tilingFactor, tintColor);
	}

	void Renderer2D::drawQuad(const glm::vec3& pos, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor){
		RENDER_PROFILE_FUNCTION();
		// This is how we are going to be drawing the texture onto the objects
		// - By first binding that texture, then when we bind that texture to that shader.
		/* _data->textureShader->setFloat4("u_Color", glm::vec4(1.0f)); */
		_data->textureShader->setFloat4("u_Color", tintColor);
		_data->textureShader->setFloat("u_TilingFactor", tilingFactor);
		texture->bind();
		
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});
		
		_data->textureShader->setMat4("u_Transform", transform);

		// Actual draw call
		_data->quadVertexArray->bind();
		RendererCommand::drawIndexed(_data->quadVertexArray);
	}
	
	void Renderer2D::drawRotatedQuad(const glm::vec2& pos, const glm::vec2& size, float rotation, const glm::vec4& color){
		drawRotatedQuad({pos.x, pos.y, 0.0f}, size, rotation, color);
	}
	
	void Renderer2D::drawRotatedQuad(const glm::vec3& pos, const glm::vec2& size, float rotation, const glm::vec4& color){
		RENDER_PROFILE_FUNCTION();
		_data->textureShader->setFloat4("u_Color", color);
		_data->textureShader->setFloat("u_TilingFactor", 1.0f);

		// Bind white texture here
		_data->whiteTexture->bind();
		
		// This is how we are going to do transformation
		// Since we aren't doing rotation, we are handling Translation(position) and Scale (size)
		// Whereas mat4(1.0f) is going to be our identity matrix
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) 
							  * glm::rotate(glm::mat4(1.0f), rotation, {0.0f, 0.0f, 1.0f})
							  * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});

		_data->textureShader->setMat4("u_Transform", transform);

		_data->quadVertexArray->bind();
		RendererCommand::drawIndexed(_data->quadVertexArray);
	}

	void Renderer2D::drawRotatedQuad(const glm::vec2& pos, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor){
		drawRotatedQuad({pos.x, pos.y, 0.0f}, size, rotation, texture, tilingFactor, tintColor);
	}

	void Renderer2D::drawRotatedQuad(const glm::vec3& pos, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor){
		RENDER_PROFILE_FUNCTION();
		_data->textureShader->setFloat4("u_Color", tintColor);
		_data->textureShader->setFloat("u_TilingFactor", tilingFactor);

		// Bind texture here
		texture->bind();
		
		// This is how we are going to do transformation
		// Since we aren't doing rotation, we are handling Translation(position) and Scale (size)
		// Whereas mat4(1.0f) is going to be our identity matrix
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) 
							  * glm::rotate(glm::mat4(1.0f), rotation, {0.0f, 0.0f, 1.0f})
							  * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});

		_data->textureShader->setMat4("u_Transform", transform);

		_data->quadVertexArray->bind();
		RendererCommand::drawIndexed(_data->quadVertexArray);
	}
};

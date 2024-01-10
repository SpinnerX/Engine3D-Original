#include <GameEnginePrecompiledHeader.h>
#include <GameEngine/Renderer/Renderer2D.h>
#include <GameEngine/Renderer/VertexArray.h>
#include <GameEngine/Renderer/RenderCommand.h>
#include <GameEngine/platforms/OpenGL/OpenGLShader.h>
#include <glm/gtc/matrix_transform.hpp>

namespace RendererEngine{
	struct quadVertex{
		glm::vec3 pos;
		glm::vec4 color;
		glm::vec2 texCoord;
		// TODO: texid
	};

	// This data wont get deleted unless we delete this manually.
	struct Renderer2DData{
		const uint32_t maxQuads = 10000; // speciying our max of quads
		const uint32_t maxVertices = maxQuads * 4; // *4 because we have 4 vertices (just checking if exceeding this max, then create another draw call.)
		const uint32_t maxIndices = maxQuads * 6; // *6 is because we have 6 indices
		Ref<VertexArray> quadVertexArray;
		Ref<VertexBuffer> quadVertexBuffer;
		Ref<Shader> textureShader;
		Ref<Texture2D> whiteTexture;

		uint32_t quadIndexCounter = 0; // Evrey time we draw a quad we increment by 6, so we know how many indices we have to draw when we flush everything.
		quadVertex* quadVertexBufferBase = nullptr;
		quadVertex* quadVertexBufferPtr = nullptr;

	};

	static Renderer2DData _data; // So this could be unique to this translation unit
	

	void Renderer2D::Init(){
		RENDER_PROFILE_FUNCTION();
		_data.quadVertexArray = VertexArray::Create();

		_data.quadVertexBuffer = VertexBuffer::Create(_data.maxVertices * sizeof(quadVertex));
		
		_data.quadVertexBuffer->setLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color" },
			{ ShaderDataType::Float2, "a_TexCoord" }
		});

		_data.quadVertexArray->addVertexBuffer(_data.quadVertexBuffer);

		_data.quadVertexBufferBase = new quadVertex[_data.maxVertices];
		_data.quadVertexBufferPtr = new quadVertex[_data.maxVertices];

		uint32_t* quadIndices = new uint32_t[_data.maxIndices];
		
		uint32_t offset = 0;
		for(uint32_t i = 0; i < _data.maxIndices; i += 6){
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;


			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;

			offset += 4;
		}

		Ref<IndexBuffer> quadIB = IndexBuffer::Create(quadIndices, _data.maxIndices);
		_data.quadVertexArray->setIndexBuffer(quadIB);

		delete[] quadIndices;


		/* uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 }; */
		/* Ref<IndexBuffer> squareIB = IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)); */
		/* _data.quadVertexArray->setIndexBuffer(squareIB); */
		
		_data.whiteTexture = Texture2D::Create(1,1);
		uint32_t whiteTextureData = 0xffffffff; // four f's for every channel
		_data.whiteTexture->setData(&whiteTextureData, sizeof(uint32_t));

		_data.textureShader = Shader::CreateShader("assets/shaders/texture.glsl");
		_data.textureShader->setInt("u_Texture", 0);
	}

	void Renderer2D::Shutdown(){
		RENDER_PROFILE_FUNCTION();
	}

	void Renderer2D::beginScene(const OrthographicCamera& camera){
		RENDER_PROFILE_FUNCTION();

		// Simply uploads the camera data
		// upload is more API specific (actual OpenGL to set that uniform)
		// Where set is just set is a much higher level concept.
		_data.textureShader->bind();
		_data.textureShader->setMat4("u_ViewProjection", camera.getViewProjectionMatrix());
		
		// Setting everything here!
		_data.quadIndexCounter = 0;
		_data.quadVertexBufferPtr = _data.quadVertexBufferBase;
	}

	void Renderer2D::endScene(){
		RENDER_PROFILE_FUNCTION();
		
		uint32_t dataSize = (uint8_t *)_data.quadVertexBufferPtr - (uint8_t *)_data.quadVertexBufferBase;
		_data.quadVertexBuffer->setData(_data.quadVertexBufferBase, dataSize); 
		flush();
	}

	void Renderer2D::flush(){
		RendererCommand::drawIndexed(_data.quadVertexArray, _data.quadIndexCounter);	
	}

	void Renderer2D::drawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color){
		drawQuad({pos.x, pos.y, 0.0f}, size, color);
	}
	
	void Renderer2D::drawQuad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color){
		RENDER_PROFILE_FUNCTION();

		_data.whiteTexture->bind();
		_data.quadVertexBufferPtr->pos = pos;
		_data.quadVertexBufferPtr->color = color;
		_data.quadVertexBufferPtr->texCoord = {0.0f, 0.0f};
		_data.quadVertexBufferPtr++;

		_data.quadVertexBufferPtr->pos = {pos.x + size.x, pos.y, 0.f};
		_data.quadVertexBufferPtr->color = color;
		_data.quadVertexBufferPtr->texCoord = {1.0f, 0.0f};
		_data.quadVertexBufferPtr++;

		_data.quadVertexBufferPtr->pos = {pos.x+size.x, pos.y+size.y, 0.f};
		_data.quadVertexBufferPtr->color = color;
		_data.quadVertexBufferPtr->texCoord = {1.0f, 1.0f};
		_data.quadVertexBufferPtr++;

		_data.quadVertexBufferPtr->pos = {pos.x, pos.y + size.y, 0.f};
		_data.quadVertexBufferPtr->color = color;
		_data.quadVertexBufferPtr->texCoord = {0.0f, 1.0f};
		_data.quadVertexBufferPtr++;

		_data.quadIndexCounter += 6;
		
		/* glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * */
		/* 					  glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f}); */
		/* _data.textureShader->setMat4("u_Transform", transform); */
		/* _data.quadVertexArray->bind(); */
		/* RendererCommand::drawIndexed(_data.quadVertexArray); */
	}
	
	void Renderer2D::drawQuad(const glm::vec2& pos, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor){
		drawQuad({pos.x, pos.y, 0.0f}, size, texture, tilingFactor, tintColor);
	}

	void Renderer2D::drawQuad(const glm::vec3& pos, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor){
		RENDER_PROFILE_FUNCTION();
		// This is how we are going to be drawing the texture onto the objects
		// - By first binding that texture, then when we bind that texture to that shader.
		/* _data->textureShader->setFloat4("u_Color", glm::vec4(1.0f)); */
		_data.textureShader->setFloat4("u_Color", tintColor);

		_data.textureShader->setFloat("u_TilingFactor", tilingFactor);
		texture->bind();
		
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});
		_data.textureShader->setMat4("u_Transform", transform);

		_data.quadVertexArray->bind();
		RendererCommand::drawIndexed(_data.quadVertexArray);
	}
	
	void Renderer2D::drawRotatedQuad(const glm::vec2& pos, const glm::vec2& size, float rotation, const glm::vec4& color){
		drawRotatedQuad({pos.x, pos.y, 0.0f}, size, rotation, color);
	}
	
	void Renderer2D::drawRotatedQuad(const glm::vec3& pos, const glm::vec2& size, float rotation, const glm::vec4& color){
		RENDER_PROFILE_FUNCTION();
		_data.textureShader->setFloat4("u_Color", color);
		_data.textureShader->setFloat("u_TilingFactor", 1.0f);

		// Bind white texture here
		_data.whiteTexture->bind();
		
		// This is how we are going to do transformation
		// Since we aren't doing rotation, we are handling Translation(position) and Scale (size)
		// Whereas mat4(1.0f) is going to be our identity matrix
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) 
							  * glm::rotate(glm::mat4(1.0f), rotation, {0.0f, 0.0f, 1.0f})
							  * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});

		_data.textureShader->setMat4("u_Transform", transform);

		_data.quadVertexArray->bind();
		RendererCommand::drawIndexed(_data.quadVertexArray);
	}

	void Renderer2D::drawRotatedQuad(const glm::vec2& pos, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor){
		drawRotatedQuad({pos.x, pos.y, 0.0f}, size, rotation, texture, tilingFactor, tintColor);
	}

	void Renderer2D::drawRotatedQuad(const glm::vec3& pos, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor){
		RENDER_PROFILE_FUNCTION();
		_data.textureShader->setFloat4("u_Color", tintColor);
		_data.textureShader->setFloat("u_TilingFactor", tilingFactor);

		// Bind texture here
		texture->bind();
		
		// This is how we are going to do transformation
		// Since we aren't doing rotation, we are handling Translation(position) and Scale (size)
		// Whereas mat4(1.0f) is going to be our identity matrix
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) 
							  * glm::rotate(glm::mat4(1.0f), rotation, {0.0f, 0.0f, 1.0f})
							  * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});

		_data.textureShader->setMat4("u_Transform", transform);

		_data.quadVertexArray->bind();
		RendererCommand::drawIndexed(_data.quadVertexArray);
	}
};

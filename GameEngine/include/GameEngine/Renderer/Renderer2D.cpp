#include <GameEnginePrecompiledHeader.h>
#include <GameEngine/Renderer/Renderer2D.h>
#include <GameEngine/Renderer/VertexArray.h>
#include <GameEngine/Renderer/RenderCommand.h>
#include <GameEngine/platforms/OpenGL/OpenGLShader.h>
#include <glm/gtc/matrix_transform.hpp>

namespace RendererEngine{
	struct quadVertex{
		glm::vec3 pos; // contains position of the texture
		glm::vec4 color; // color the texture contains
		glm::vec2 texCoord;
		float texIndex; // containing whatever texture we have (if zero then it'll sample from white texture and draw nothing)
		float tilingFactor;
	};

	// This data wont get deleted unless we delete this manually.
	struct Renderer2DData{
		static const uint32_t maxQuads = 10000; // max for how many quads we can Render
		static const uint32_t maxVertices = maxQuads * 4; // max of vertices we can have every single draw quad
		static const uint32_t maxIndices = maxQuads * 6; // Since we have around 6 indices per quad
		static const uint32_t maxTextureSlots = 16; // Mac = 16, Windows maybe = 32.
		Ref<VertexArray> quadVertexArray;
		Ref<VertexBuffer> quadVertexBuffer;
		Ref<Shader> textureShader;
		Ref<Texture2D> whiteTexture;
		uint32_t quadIndexCount = 0;
		quadVertex* quadVertexBufferBase = nullptr;
		quadVertex* quadVertexBufferPtr = nullptr;

		std::array<Ref<Texture2D>, maxTextureSlots> textureSlots;
		uint32_t textureSlotIndex = 1; // 0 - white texture
		glm::vec4 quadVertexPositions[4];

		Renderer2D::Statistics stats;
	};

	static Renderer2DData _data; // So this could be unique to this translation unit

	void Renderer2D::Init(){
		RENDER_PROFILE_FUNCTION();
		_data.quadVertexArray = VertexArray::Create();

		_data.quadVertexBuffer = VertexBuffer::Create(_data.maxVertices * sizeof(quadVertex));
		
		_data.quadVertexBuffer->setLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color" },
			{ ShaderDataType::Float2, "a_TexCoord" },
			{ ShaderDataType::Float, "a_TexIndex" },
			{ ShaderDataType::Float, "a_TilingFactor" }
		});

		_data.quadVertexArray->addVertexBuffer(_data.quadVertexBuffer);
		
		_data.quadVertexBufferBase = new quadVertex[_data.maxVertices * sizeof(quadVertex)];


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

		_data.whiteTexture = Texture2D::Create(1,1);
		uint32_t whiteTextureData = 0xffffffff; // four f's for every channel
		_data.whiteTexture->setData(&whiteTextureData, sizeof(uint32_t));

		int32_t samplers[_data.maxTextureSlots];
		for(uint32_t i = 0; i < _data.maxTextureSlots; i++)
			samplers[i] = i;

		_data.textureShader = Shader::CreateShader("assets/shaders/texture.glsl");
		_data.textureShader->bind();
		_data.textureShader->setIntArray("u_Textures", samplers, _data.maxTextureSlots);

		// Texture slot at 0 to white texture
		_data.textureSlots[0] = _data.whiteTexture;
		_data.quadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f};
		_data.quadVertexPositions[1] = { 0.5f, -0.5f, 0.0f, 1.0f};
		_data.quadVertexPositions[2] = { 0.5f, 0.5f, 0.0f, 1.0f};
		_data.quadVertexPositions[3] = { -0.5f, 0.5f, 0.0f, 1.0f};
	}

	void Renderer2D::Shutdown(){
		RENDER_PROFILE_FUNCTION();
	}

	void Renderer2D::beginScene(const OrthographicCamera& camera){
		RENDER_PROFILE_FUNCTION();

		// Simply uploads the camera data
		// upload is more API specific (actual OpenGL to set that uniform)
		// Where set is just set is a much higher level concept.
		_data.textureShader->setMat4("u_ViewProjection", camera.getViewProjectionMatrix());
		
		_data.quadIndexCount = 0;
		_data.quadVertexBufferPtr = _data.quadVertexBufferBase; // Keeping track o our base memory allocations
		
		_data.textureSlotIndex = 1;
	}

	void Renderer2D::endScene(){
		RENDER_PROFILE_FUNCTION();
		
		uint32_t dataSize = (uint8_t *)_data.quadVertexBufferPtr - (uint8_t *)_data.quadVertexBufferBase;
		_data.quadVertexBuffer->setData(_data.quadVertexBufferBase, dataSize);

		// Actually doing the rendering, essentially flushing
		// Uploading data to GPU
		flush();
	}

	void Renderer2D::flush(){
		RENDER_PROFILE_FUNCTION();

		// Iterating based on whatever textures we've submitted
		// Binding the correct textures
		for(uint32_t i = 0; i < _data.textureSlotIndex; i++)
			_data.textureSlots[i]->bind(i);
		
		RendererCommand::drawIndexed(_data.quadVertexArray, _data.quadIndexCount);
		_data.stats.drawCalls++;
	}

	void Renderer2D::flushAndReset(){
		endScene();
		_data.quadIndexCount = 0;
		_data.quadVertexBufferPtr = _data.quadVertexBufferBase; // Keeping track o our base memory allocations
		
		_data.textureSlotIndex = 1;
		
	}

	void Renderer2D::drawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color){
		drawQuad({pos.x, pos.y, 0.0f}, size, color);
	}
	
	void Renderer2D::drawQuad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color){
		RENDER_PROFILE_FUNCTION();
		
		// To prevent overflow.
		if(_data.quadIndexCount >= Renderer2DData::maxIndices){
			flushAndReset();
		}
		constexpr size_t quadVertexCount = 4;
		constexpr glm::vec2 textureCoords[] = { {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}};
		
		const float textureIndex = 0.0f; // Being our white texture
		const float tilingFactor = 1.0f;
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos)
							  * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});

		for(size_t i = 0; i < quadVertexCount; i++){	
			_data.quadVertexBufferPtr->pos = transform * _data.quadVertexPositions[i];
			_data.quadVertexBufferPtr->color = color;
			_data.quadVertexBufferPtr->texCoord = textureCoords[i];
			_data.quadVertexBufferPtr->texIndex = textureIndex;
			_data.quadVertexBufferPtr->tilingFactor = tilingFactor;
			_data.quadVertexBufferPtr++;
		}

		_data.quadIndexCount += 6;

		_data.stats.quadCount++;
	}
	
	void Renderer2D::drawQuad(const glm::vec2& pos, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor){
		drawQuad({pos.x, pos.y, 0.0f}, size, texture, tilingFactor, tintColor);
	}

	void Renderer2D::drawQuad(const glm::vec3& pos, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor){
		RENDER_PROFILE_FUNCTION();
		// To prevent overflow.
		if(_data.quadIndexCount >= Renderer2DData::maxIndices){
			flushAndReset();
		}
		
		constexpr float x = 7, y = 6;
		constexpr float sheetWidth = 2560, sheetHeight = 1664;
		constexpr float spriteWidth = 128.0f, spriteHeight = 128.0f;

		constexpr glm::vec4 color = {1.0f, 1.0f, 1.0f, 1.0f};
		constexpr size_t quadVertexCount = 4;

		constexpr glm::vec2 textureCoords[] = {
			{(x * spriteWidth) / sheetWidth, (y * spriteHeight) / sheetHeight},
			{((x + 1) * spriteWidth) / sheetWidth, (y * spriteHeight) / sheetHeight},
			{((x + 1) * spriteWidth) / sheetWidth, ((y + 1) * spriteHeight) / sheetHeight},
			{(x * spriteWidth) / sheetWidth, ((y + 1) * spriteHeight) / sheetHeight}};



		float textureIndex = 0.0f;
		// Searching for texture index in our array.
		for(uint32_t i = 1; i < _data.textureSlotIndex; i++){
			if(*_data.textureSlots[i].get() == *texture.get()){
				textureIndex = (float)i;
				break;
			}
		}

		if(textureIndex == 0.0f){
			textureIndex = (float)_data.textureSlotIndex; // assign to next available texture slot. Should be 1
			_data.textureSlots[_data.textureSlotIndex] = texture;
			_data.textureSlotIndex++;
		}

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos)
							  * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});
		
		for(size_t i = 0; i  < quadVertexCount; i++){
			_data.quadVertexBufferPtr->pos = transform * _data.quadVertexPositions[i];
			_data.quadVertexBufferPtr->color = color;
			_data.quadVertexBufferPtr->texCoord = textureCoords[i];
			_data.quadVertexBufferPtr->texIndex = textureIndex;
			_data.quadVertexBufferPtr->tilingFactor = tilingFactor;
			_data.quadVertexBufferPtr++;
		}

		_data.quadIndexCount += 6;

		_data.stats.quadCount++;
	}

	void Renderer2D::drawQuad(const glm::vec2& pos, const glm::vec2& size, const Ref<SubTexture2D>& subTexture, float tilingFactor, const glm::vec4& tintColor){
		drawQuad({pos.x, pos.y, 0.0f}, size, subTexture, tilingFactor, tintColor);
	}

	void Renderer2D::drawQuad(const glm::vec3& pos, const glm::vec2& size, const Ref<SubTexture2D>& subTexture, float tilingFactor, const glm::vec4& tintColor){
		RENDER_PROFILE_FUNCTION();
		// To prevent overflow.
		if(_data.quadIndexCount >= Renderer2DData::maxIndices){
			flushAndReset();
		}
		
		constexpr size_t quadVertexCount = 4;
		const glm::vec2* textureCoords = subTexture->getTexCoords();
		const Ref<Texture2D> texture = subTexture->getTexture();

		constexpr glm::vec4 color = {1.0f, 1.0f, 1.0f, 1.0f};

		float textureIndex = 0.0f;
		// Searching for texture index in our array.
		for(uint32_t i = 1; i < _data.textureSlotIndex; i++){
			if(*_data.textureSlots[i].get() == *texture.get()){
				textureIndex = (float)i;
				break;
			}
		}

		if(textureIndex == 0.0f){
			textureIndex = (float)_data.textureSlotIndex; // assign to next available texture slot. Should be 1
			_data.textureSlots[_data.textureSlotIndex] = texture;
			_data.textureSlotIndex++;
		}

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos)
							  * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});
	
		for(size_t i = 0; i < quadVertexCount; i++){
			_data.quadVertexBufferPtr->pos = transform * _data.quadVertexPositions[i];
			_data.quadVertexBufferPtr->color = color;
			_data.quadVertexBufferPtr->texCoord = textureCoords[i];
			_data.quadVertexBufferPtr->texIndex = textureIndex;
			_data.quadVertexBufferPtr->tilingFactor = tilingFactor;
			_data.quadVertexBufferPtr++;
		}

		_data.quadIndexCount += 6;

		_data.stats.quadCount++;
	}
	
	void Renderer2D::drawRotatedQuad(const glm::vec2& pos, const glm::vec2& size, float rotation, const glm::vec4& color){
		drawRotatedQuad({pos.x, pos.y, 0.0f}, size, rotation, color);
	}
	
	void Renderer2D::drawRotatedQuad(const glm::vec3& pos, const glm::vec2& size, float rotation, const glm::vec4& color){
		RENDER_PROFILE_FUNCTION();
		// To prevent overflow.
		if(_data.quadIndexCount >= Renderer2DData::maxIndices){
			flushAndReset();
		}

		constexpr size_t quadVertexCount = 4;
		constexpr glm::vec2 textureCoords[] = { {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}};

		const float textureIndex = 0.0f; // Being our white texture
		const float tilingFactor = 1.0f;

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos)
							  * glm::rotate(glm::mat4(1.0f), rotation, {0.0f, 0.0f, 1.0f})
							  * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});
		
		for(size_t i = 0; i < quadVertexCount; i++){
			_data.quadVertexBufferPtr->pos = transform * _data.quadVertexPositions[i];
			_data.quadVertexBufferPtr->color = color;
			_data.quadVertexBufferPtr->texCoord = textureCoords[i];
			_data.quadVertexBufferPtr->texIndex = textureIndex;
			_data.quadVertexBufferPtr->tilingFactor = tilingFactor;
			_data.quadVertexBufferPtr++;
		}

		_data.quadIndexCount += 6;

		_data.stats.quadCount++;

	}

	void Renderer2D::drawRotatedQuad(const glm::vec2& pos, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor){
		drawRotatedQuad({pos.x, pos.y, 0.0f}, size, rotation, texture, tilingFactor, tintColor);
	}

	void Renderer2D::drawRotatedQuad(const glm::vec3& pos, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor){
		RENDER_PROFILE_FUNCTION();
		// To prevent overflow.
		if(_data.quadIndexCount >= Renderer2DData::maxIndices){
			flushAndReset();
		}
		
		constexpr size_t quadVertexCount = 4;
		constexpr glm::vec2 textureCoords[] = { {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}};

		constexpr glm::vec4 color = {1.0f, 1.0f, 1.0f, 1.0f};

		float textureIndex = 0.0f;
		// Searching for texture index in our array.
		for(uint32_t i = 1; i < _data.textureSlotIndex; i++){
			if(*_data.textureSlots[i].get() == *texture.get()){
				textureIndex = (float)i;
				break;
			}
		}

		if(textureIndex == 0.0f){
			textureIndex = (float)_data.textureSlotIndex; // assign to next available texture slot. Should be 1
			_data.textureSlots[_data.textureSlotIndex] = texture;
			_data.textureSlotIndex++;
		}

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos)
							  * glm::rotate(glm::mat4(1.0f), rotation, {0.0f, 0.0f, 1.0f})
							  * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});
	
		for(size_t i = 0; i < quadVertexCount; i++){
			_data.quadVertexBufferPtr->pos = transform * _data.quadVertexPositions[i];
			_data.quadVertexBufferPtr->color = color;
			_data.quadVertexBufferPtr->texCoord = textureCoords[i];
			_data.quadVertexBufferPtr->texIndex = textureIndex;
			_data.quadVertexBufferPtr->tilingFactor = tilingFactor;
			_data.quadVertexBufferPtr++;
		}

		_data.quadIndexCount += 6;

		_data.stats.quadCount++;
	}
	
	void Renderer2D::drawRotatedQuad(const glm::vec2& pos, const glm::vec2& size, float rotation, const Ref<SubTexture2D>& subTexture, float tilingFactor, const glm::vec4& tintColor){
		drawRotatedQuad({pos.x, pos.y, 0.0f}, size, rotation, subTexture, tilingFactor, tintColor);
	}

	void Renderer2D::drawRotatedQuad(const glm::vec3& pos, const glm::vec2& size, float rotation, const Ref<SubTexture2D>& subTexture, float tilingFactor, const glm::vec4& tintColor){
		RENDER_PROFILE_FUNCTION();
		// To prevent overflow.
		if(_data.quadIndexCount >= Renderer2DData::maxIndices){
			flushAndReset();
		}
		
		constexpr size_t quadVertexCount = 4;
		const glm::vec2* textureCoords = subTexture->getTexCoords();
		const Ref<Texture2D> texture = subTexture->getTexture();

		constexpr glm::vec4 color = {1.0f, 1.0f, 1.0f, 1.0f};

		float textureIndex = 0.0f;
		// Searching for texture index in our array.
		for(uint32_t i = 1; i < _data.textureSlotIndex; i++){
			if(*_data.textureSlots[i].get() == *texture.get()){
				textureIndex = (float)i;
				break;
			}
		}

		if(textureIndex == 0.0f){
			textureIndex = (float)_data.textureSlotIndex; // assign to next available texture slot. Should be 1
			_data.textureSlots[_data.textureSlotIndex] = texture;
			_data.textureSlotIndex++;
		}

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos)
							  * glm::rotate(glm::mat4(1.0f), rotation, {0.0f, 0.0f, 1.0f})
							  * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});
	
		for(size_t i = 0; i < quadVertexCount; i++){
			_data.quadVertexBufferPtr->pos = transform * _data.quadVertexPositions[i];
			_data.quadVertexBufferPtr->color = color;
			_data.quadVertexBufferPtr->texCoord = textureCoords[i];
			_data.quadVertexBufferPtr->texIndex = textureIndex;
			_data.quadVertexBufferPtr->tilingFactor = tilingFactor;
			_data.quadVertexBufferPtr++;
		}

		_data.quadIndexCount += 6;

		_data.stats.quadCount++;
	}

	Renderer2D::Statistics Renderer2D::getStats(){ return _data.stats; }

	void Renderer2D::resetStats(){
		memset(&_data.stats, 0, sizeof(Statistics));
	}
};

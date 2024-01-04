#include <GameEnginePrecompiledHeader.h>
#include <GameEngine/Renderer/Renderer2D.h>
#include <GameEngine/platforms/OpenGL/OpenGLShader.h>
#include <GameEngine/Renderer/RenderCommand.h>

namespace RendererEngine{

	// This data wont get deleted unless we delete this manually.
	struct Renderer2DStorage{
		Ref<VertexArray> quadVertexArray;
		Ref<Shader> flatColorShader;
	};

	static Renderer2DStorage* _data = nullptr; // So this could be unique to this translation unit

	void Renderer2D::Init(){
		_data = new Renderer2DStorage();
		_data->quadVertexArray = VertexArray::Create();

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		Ref<VertexBuffer> squareVB;
		squareVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		
		squareVB->setLayout({
			{ ShaderDataType::Float3, "a_Position" }
		});

		_data->quadVertexArray->addVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Ref<IndexBuffer> squareIB;
		squareIB.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		_data->quadVertexArray->setIndexBuffer(squareIB);

		/* _flatColorShader = Shader::Create("assets/shaders/FlatColor.glsl"); */
		_data->flatColorShader = Shader::CreateShader("assets/sandbox2DShaders/FlatColor.glsl");
	}

	void Renderer2D::Shutdown(){
		delete _data; // dont want to automatically delete this (ref to using smart ptrs), because we want them deleted when the 2D renderer shuts down.
	}

	void Renderer2D::beginScene(const OrthographicCamera& camera){
		
		// Simply uploads the camera data
		std::dynamic_pointer_cast<OpenGLShader>(_data->flatColorShader)->bind();
		std::dynamic_pointer_cast<RendererEngine::OpenGLShader>(_data->flatColorShader)->uploadUniformMat4("u_ViewProjection", camera.getProjectionMatrix());
		std::dynamic_pointer_cast<RendererEngine::OpenGLShader>(_data->flatColorShader)->uploadUniformMat4("u_Transform", glm::mat4(1.0f));
	}

	void Renderer2D::endScene(){

	}

	void Renderer2D::drawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color){
		drawQuad({pos.x, pos.y, 0.0f}, size, color);
	}
	
	void Renderer2D::drawQuad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color){
		std::dynamic_pointer_cast<OpenGLShader>(_data->flatColorShader)->bind();
		std::dynamic_pointer_cast<RendererEngine::OpenGLShader>(_data->flatColorShader)->uploadUniformFloat4("u_Color", color);

		// Actual draw call
		_data->quadVertexArray->bind();
		RendererCommand::drawIndexed(_data->quadVertexArray);

	}
		
};

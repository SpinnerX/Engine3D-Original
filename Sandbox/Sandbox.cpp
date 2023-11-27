#include <GameEngine/GameEngine.h>

// This is just an example on how to make a layer
class ExampleLayer : public RendererEngine::Layer{
public:
    ExampleLayer() : Layer("Example"), _camera(-1.6f, 1.6f, -0.9f, 0.9f), _cameraPosition(0.0f, 0.0f, 0.0f){
        _vertexArray.reset(RendererEngine::VertexArray::Create());

        float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

        std::shared_ptr<RendererEngine::VertexBuffer> _vertexBuffer;
        _vertexBuffer.reset(RendererEngine::VertexBuffer::Create(vertices, sizeof(vertices)));

       RendererEngine::BufferLayout bufLayout = {
            {RendererEngine::ShaderDataType::Float3, "a_Position", true},
            {RendererEngine::ShaderDataType::Float4, "a_Color", true},
       };

       _vertexBuffer->setLayout(bufLayout);
       _vertexArray->addVertexBuffer(_vertexBuffer);

        std::shared_ptr<RendererEngine::IndexBuffer> _indexBuffer;
        uint32_t indices[3] = {0, 1, 2};
        _indexBuffer.reset(RendererEngine::IndexBuffer::Create(indices,  sizeof(indices) / sizeof(uint32_t)));
        _vertexArray->setIndexBuffer(_indexBuffer);
        

        //////////////////////////
        // Square Vertex Data //
        //////////////////////////

        float squareVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
             -0.75f,  0.75f, 0.0f,
		};

        _squareVertexArrays.reset(RendererEngine::VertexArray::Create());
        std::shared_ptr<RendererEngine::VertexBuffer> squareVB;
        squareVB.reset(RendererEngine::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

        squareVB->setLayout({
            {RendererEngine::ShaderDataType::Float3, "a_Position", true},
        });
        _squareVertexArrays->addVertexBuffer(squareVB);

        uint32_t squareIndices[6] = {0, 1, 2, 2, 3, 0};
        std::shared_ptr<RendererEngine::IndexBuffer> squareIB;
        squareIB.reset(RendererEngine::IndexBuffer::Create(squareIndices,  sizeof(squareIndices) / sizeof(uint32_t)));
        _squareVertexArrays->setIndexBuffer(squareIB);

        std::string vertexSrc = R"(
			#version 330 core
			
            uniform mat4 u_ViewProjection;

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

        _shader  = std::make_shared<RendererEngine::Shader>(vertexSrc, fragmentSrc);
        std::string blueShaderVertexSrc = R"(
			#version 330 core

            uniform mat4 u_ViewProjection;

			layout(location = 0) in vec3 a_Position;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
			}
		)";

		std::string blueShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

        _blueShader = std::make_shared<RendererEngine::Shader>(blueShaderVertexSrc, blueShaderFragmentSrc);
    }

    virtual void onUpdate() override {
        // if(RendererEngine::InputPoll::isKeyPressed(RENDER_KEY_D)){ // RIGHT
        if(RendererEngine::InputPoll::isKeyPressed(RENDER_KEY_RIGHT)){ // RIGHT
            _cameraPosition.x -= _cameraMoveSpeed;
        }
        else if(RendererEngine::InputPoll::isKeyPressed(RENDER_KEY_LEFT)){ // LEFT
            _cameraPosition.x += _cameraMoveSpeed;
        }
        // if(RendererEngine::InputPoll::isKeyPressed(RENDER_KEY_W)){ // UP
        else if(RendererEngine::InputPoll::isKeyPressed(RENDER_KEY_UP)){ // UP
            _cameraPosition.y -= _cameraMoveSpeed;
        }
        // if(RendererEngine::InputPoll::isKeyPressed(RENDER_KEY_S)){ // DOWN
        if(RendererEngine::InputPoll::isKeyPressed(RENDER_KEY_DOWN)){ // DOWN
            _cameraPosition.y += _cameraMoveSpeed;
        }

        if(RendererEngine::InputPoll::isKeyPressed(RENDER_KEY_A)){ // LEFT
            _cameraRotation += _cameraRotationSpeed;
        }
        else if(RendererEngine::InputPoll::isKeyPressed(RENDER_KEY_D)){ // RIGHT
            _cameraRotation -= _cameraRotationSpeed;
        }

        RendererEngine::RendererCommand::setClearColor({0.1f, 0.1f, 0.1f, 1});
        RendererEngine::RendererCommand::clear();
        // printf("Camera Position: (%f, %f, %f\n", _cameraPosition.x, _cameraPosition.y, _cameraPosition.z);
        _camera.setPosition(_cameraPosition); // {x, y, z} (Changing Camera Position)
        _camera.setRotation(_cameraRotation);

        RendererEngine::Renderer::beginScene(_camera); // BeginScene

        RendererEngine::Renderer::submit(_blueShader, _squareVertexArrays);
        RendererEngine::Renderer::submit(_shader, _vertexArray); // Submitting our  objects or even meshes (or geo meshes)

        RendererEngine::Renderer::endScene(); // EndScene
    }

    virtual void onEvent(RendererEngine::Event& event) override {
        auto bind_function = [](auto* instance, auto member_function){
            return [instance, member_function](auto&& arg1){
                return (instance->*member_function)(std::forward<decltype(arg1)>(arg1));
            };
        };
    }

private:
    std::shared_ptr<RendererEngine::Shader> _shader;
    std::shared_ptr<RendererEngine::VertexArray> _vertexArray;

    std::shared_ptr<RendererEngine::Shader> _blueShader;
    std::shared_ptr<RendererEngine::VertexArray> _squareVertexArrays;

    RendererEngine::OrthographicCamera _camera;

    float _cameraMoveSpeed = 0.1f;
    float _cameraRotation = 0.0f;
    float _cameraRotationSpeed = 2.0f;
    glm::vec3 _cameraPosition;
};

class Sandbox : public RendererEngine::Application{
public:
    Sandbox() : RendererEngine::Application() {
        pushLayer(new ExampleLayer());
    }

    ~Sandbox() {}
};

RendererEngine::Application* RendererEngine::CreateApplication(){
    return new Sandbox();
}
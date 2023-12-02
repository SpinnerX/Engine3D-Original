#include <GameEngine/GameEngine.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GameEngine/platforms/OpenGL/OpenGLShader.h>

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

        RendererEngine::Ref<RendererEngine::VertexBuffer> _vertexBuffer;
        _vertexBuffer.reset(RendererEngine::VertexBuffer::Create(vertices, sizeof(vertices)));

       RendererEngine::BufferLayout bufLayout = {
            {RendererEngine::ShaderDataType::Float3, "a_Position", true},
            {RendererEngine::ShaderDataType::Float4, "a_Color", true},
       };

       _vertexBuffer->setLayout(bufLayout);
       _vertexArray->addVertexBuffer(_vertexBuffer);

        RendererEngine::Ref<RendererEngine::IndexBuffer> _indexBuffer;
        uint32_t indices[3] = {0, 1, 2};
        _indexBuffer.reset(RendererEngine::IndexBuffer::Create(indices,  sizeof(indices) / sizeof(uint32_t)));
        _vertexArray->setIndexBuffer(_indexBuffer);
        

        //////////////////////////
        // Square Vertex Data //
        //////////////////////////
        
        float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
             -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

        _squareVertexArrays.reset(RendererEngine::VertexArray::Create());
        RendererEngine::Ref<RendererEngine::VertexBuffer> squareVB;
        squareVB.reset(RendererEngine::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

        squareVB->setLayout({
            {RendererEngine::ShaderDataType::Float3, "a_Position", true},
            {RendererEngine::ShaderDataType::Float2, "a_TexCoord", true}
        });
        _squareVertexArrays->addVertexBuffer(squareVB);

        uint32_t squareIndices[6] = {0, 1, 2, 2, 3, 0};
        RendererEngine::Ref<RendererEngine::IndexBuffer> squareIB;
        squareIB.reset(RendererEngine::IndexBuffer::Create(squareIndices,  sizeof(squareIndices) / sizeof(uint32_t)));
        _squareVertexArrays->setIndexBuffer(squareIB);

        std::string vertexSrc = R"(
			#version 330 core
			
            uniform mat4 u_ViewProjection;
            uniform mat4 u_Transform;

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
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

        // _shader  = std::make_shared<RendererEngine::Shader>(vertexSrc, fragmentSrc);
        _shader.reset(RendererEngine::Shader::CreateShader(vertexSrc, fragmentSrc));
        std::string blueShaderVertexSrc = R"(
			#version 330 core

            uniform mat4 u_ViewProjection;
            uniform mat4 u_Transform;


			layout(location = 0) in vec3 a_Position;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

            uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

        _flatShader.reset(RendererEngine::Shader::CreateShader(blueShaderVertexSrc, flatColorShaderFragmentSrc));

        std::string textureShaderVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec2 a_TexCoord;
            
            uniform mat4 u_ViewProjection;
            uniform mat4 u_Transform;

			out vec2 v_TexCoord;


			void main()
			{
                v_TexCoord = a_TexCoord;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string textureShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec2 v_TexCoord;

            uniform sampler2D u_Texture;

			void main()
			{
				color = texture(u_Texture, v_TexCoord);
			}
		)";

        _textureShader.reset(RendererEngine::Shader::CreateShader(textureShaderVertexSrc, textureShaderFragmentSrc));
        
        _texture = RendererEngine::Texture2D::Create("../assets/Checkerboard.png");
        std::dynamic_pointer_cast<RendererEngine::OpenGLShader>(_textureShader)->bind();
        std::dynamic_pointer_cast<RendererEngine::OpenGLShader>(_textureShader)->uploadUniformInt("u_Texture", 0);
    }

    virtual void onUpdate(RendererEngine::Timestep ts) override {
        RendererEngine::RendererCommand::setClearColor({0.1f, 0.1f, 0.1f, 1});
        RendererEngine::RendererCommand::clear();
        float time = ts;
        
        if(RendererEngine::InputPoll::isKeyPressed(RENDER_KEY_RIGHT)){ // RIGHT
            _cameraPosition.x -= _cameraMoveSpeed * ts;
        }
        else if(RendererEngine::InputPoll::isKeyPressed(RENDER_KEY_LEFT)){ // LEFT
            _cameraPosition.x += _cameraMoveSpeed * ts;
        }
        else if(RendererEngine::InputPoll::isKeyPressed(RENDER_KEY_UP)){ // UP
            _cameraPosition.y -= _cameraMoveSpeed * ts;
        }
        else if(RendererEngine::InputPoll::isKeyPressed(RENDER_KEY_DOWN)){ // DOWN
            _cameraPosition.y += _cameraMoveSpeed * ts;
        }

        if(RendererEngine::InputPoll::isKeyPressed(RENDER_KEY_A)){ // LEFT
            _cameraRotation += _cameraRotationSpeed * ts;
        }
        else if(RendererEngine::InputPoll::isKeyPressed(RENDER_KEY_D)){ // RIGHT
            _cameraRotation -= _cameraRotationSpeed * ts;
        }

        _camera.setPosition(_cameraPosition); // {x, y, z} (Changing Camera Position)
        _camera.setRotation(_cameraRotation);
        RendererEngine::Renderer::beginScene(_camera); // BeginScene

        // Logic Flow
        // We take in a 4x4 matrix default ot 1.0
        // Then take a vec3 for the squares position, and then we translate the matrix
        // This is to get our transformation matrix to change the position of the square.
        // This is how we may scale the squares down to be a specific size
        glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

        // The Idea that we'd want when we load in a material
        // The logc behind this material
        // - Is to take in the shader, and all the data corresponding to that specific shader
        // RendererEngine::MaterialRef material = new RendererEngine::Material(_flatColorShader);
        // material->set("u_Color", redColor);

        std::dynamic_pointer_cast<RendererEngine::OpenGLShader>(_flatShader)->bind();
        std::dynamic_pointer_cast<RendererEngine::OpenGLShader>(_flatShader)->uploadUniformFloat3("u_Color", _squareColor);

        for(int i = 0; i < 20; i++){
            for(int j = 0; j < 20; j++){
                // We set the position to these squares, then space them out by 0.11f
                // Then we translate our matrix with our vec3 position, then to have consistent scaling
                //  we multiply our translated matrix with the scale.
                glm::vec3 pos(j * 0.11f, i * 0.11f, 0.0f);
                glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;

                RendererEngine::Renderer::submit(_flatShader, _squareVertexArrays, transform);
            }
        }

        _texture->bind();

        RendererEngine::Renderer::submit(_textureShader, _squareVertexArrays, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

        // Line to render a triangle
        // RendererEngine::Renderer::submit(_shader, _vertexArray); // Submitting our  objects or even meshes (or geo meshes)

        RendererEngine::Renderer::endScene(); // EndScene
    }

    virtual void onImguiRender() override{
        // Rendering a UI to allow adjust the color through a UI (called settings)
        ImGui::Begin("Settings");
        ImGui::ColorEdit3("Square Color", glm::value_ptr(_squareColor));
        ImGui::End();
    }

    virtual void onEvent(RendererEngine::Event& event) override {
    }

private:
    RendererEngine::Ref<RendererEngine::Shader> _shader;
    RendererEngine::Ref<RendererEngine::VertexArray> _vertexArray;

    RendererEngine::Ref<RendererEngine::Shader> _flatShader, _textureShader;
    RendererEngine::Ref<RendererEngine::VertexArray> _squareVertexArrays;

    RendererEngine::OrthographicCamera _camera;

    float _cameraMoveSpeed = 5.0f;
    float _cameraRotation = 0.0f;
    float _cameraRotationSpeed = 180.0f;
    glm::vec3 _cameraPosition;


    glm::vec3 _squareColor = {0.2f, 0.3f, 0.8f};

    RendererEngine::Ref<RendererEngine::Texture2D> _texture;
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
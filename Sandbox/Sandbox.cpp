#include <GameEngine/Core/GameEngine.h>
#include <cstdint>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <sys/types.h>
#include "Sandbox2D.h"
#include <GameEngine/Core/EntryPoint.h>

// This is just an example on how to make a layer
class ExampleLayer : public RendererEngine::Layer{
public:
    ExampleLayer() : Layer("Example"), _cameraController(1280.f/720.f){
        _vertexArray = RendererEngine::VertexArray::Create();

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
        _indexBuffer.reset(RendererEngine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
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

        _squareVertexArrays = RendererEngine::VertexArray::Create();
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

        // If we weren't calling Shader::Create(filpeath), then we'd call Shader::Create(vertexSrc, fragmentSrc);
        // Which would be called: Shader::CreateShader(name, vertexSrc, fragmentSrc);
        // _shader = RendererEngine::Shader::CreateShader("../assets/shaders/firstShader.glsl");
        auto _shader = _shaderLibrary.load("assets/shaders/firstShader.glsl");

        // _flatShader = RendererEngine::Shader::CreateShader("../assets/shaders/flatShader.glsl");
        auto _flatShader = _shaderLibrary.load("assets/shaders/flatShader.glsl");


        auto _textureShader = _shaderLibrary.load("assets/shaders/textureShader.glsl");
        
        _texture = RendererEngine::Texture2D::Create("assets/Checkerboard.png");
        _textureWithAlpha = RendererEngine::Texture2D::Create("assets/texture2.png");

        std::dynamic_pointer_cast<RendererEngine::OpenGLShader>(_textureShader)->bind();
        std::dynamic_pointer_cast<RendererEngine::OpenGLShader>(_textureShader)->uploadUniformInt("u_Texture", 0);
    }

    virtual void onUpdate(RendererEngine::Timestep ts) override {
		// onUpdate
		_cameraController.onUpdate(ts);
        RendererEngine::RendererCommand::setClearColor({0.1f, 0.1f, 0.1f, 1});
        RendererEngine::RendererCommand::clear();
        
        RendererEngine::Renderer::beginScene(_cameraController.getCamera());

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
		
		// TODO: Adding these functions: Shader::SetMat4, and Shader::SetFloat4
        std::dynamic_pointer_cast<RendererEngine::OpenGLShader>(_shaderLibrary.get("flatShader"))->bind();
        std::dynamic_pointer_cast<RendererEngine::OpenGLShader>(_shaderLibrary.get("flatShader"))->uploadUniformFloat3("u_Color", _squareColor);

        for(int i = 0; i < 20; i++){
            for(int j = 0; j < 20; j++){
                // We set the position to these squares, then space them out by 0.11f
                // Then we translate our matrix with our vec3 position, then to have consistent scaling
                //  we multiply our translated matrix with the scale.
                glm::vec3 pos(j * 0.11f, i * 0.11f, 0.0f);
                glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;

                RendererEngine::Renderer::submit(_shaderLibrary.get("flatShader"), _squareVertexArrays, transform);
            }
        }

        auto textureShader = _shaderLibrary.get("textureShader");
        _texture->bind();
        RendererEngine::Renderer::submit(textureShader, _squareVertexArrays, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

        _textureWithAlpha->bind();
        // RendererEngine::Renderer::submit(_textureShader, _squareVertexArrays, 
        //         glm::translate(glm::mat4(1.0f), glm::vec3(0.25f, -0.25f, 0.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
        RendererEngine::Renderer::submit(textureShader, _squareVertexArrays, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

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
		_cameraController.onEvent(event);
    }

private:
    RendererEngine::ShaderLibrary _shaderLibrary;
    RendererEngine::Ref<RendererEngine::VertexArray> _vertexArray;

    RendererEngine::Ref<RendererEngine::VertexArray> _squareVertexArrays;

    RendererEngine::OrthographicCameraController _cameraController;
    glm::vec3 _cameraPosition;

    glm::vec3 _squareColor = {0.2f, 0.3f, 0.8f};

    RendererEngine::Ref<RendererEngine::Texture2D> _texture, _textureWithAlpha;
};

class Sandbox : public RendererEngine::Application{
public:
    Sandbox() : RendererEngine::Application() {
        /* pushLayer(new ExampleLayer()); */
		pushLayer(new Sandbox2D());
    }

    ~Sandbox() {}
};

RendererEngine::Application* RendererEngine::CreateApplication(){
    return new Sandbox();
}

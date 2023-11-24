#include "Application.h"
#include <GLFW/glfw3.h>
#include <GameEngine/platforms/Windows/WindowsInput.h>

namespace RendererEngine{
    Application* Application::_instance = nullptr;
    
    Application::Application(){
        render_core_assert(!_instance, "Application already exists!");
        isRunning = true;
        _instance = this;
        _window = std::unique_ptr<Window>(Window::create());

        // Reasons not to use std::bind
        // Instead of using std::bind because of using more ram, and runtime, compile time overhead
        // using a lambda would be a better way to achhieve this
        // Usage:
        // we pass in an instance, and member function
        // As this lambda will accept that as the parameters

        // What is happening in this lambda?
        // - This lambda creates another lambda that captures the instance and member function
        // - From enclosing in this lambda. The new lambda which is a callable object and member function ptr
        // - what we are returning is a dereferenced member function ptr of variable "member_function" on object instance
        // - Then we std::forward arg1 which will just check here that if the object is a moved object or temp
        //      then it becomes an rvalue
        // - Though if object is persistent object then we use std::forward to decltype the arg1 getting actual type.
        // - Which simply just means Invoking a bound member function with a given argument.
        // - Invoking just means calling a function bounded by a class or is a specific objects method.
        auto bind_function = [](auto* instance, auto M){
            return [instance, M](auto&& arg1){
                return (instance->*M)(std::forward<decltype(arg1)>(arg1));
            };
        };
        _window->setEventCallback(bind_function(this, &Application::onEvent));
        _imguiLayer = new ImGuiLayer();
        pushOverlay(_imguiLayer);

        // Vertex Array
        // Vertex Buffer
        // Index Buffer

        // gen vertex array and bind them
        glGenVertexArrays(1, &_vertexArr);
        glBindVertexArray(_vertexArr);

        // gen vertex vertex buffer and bind them
        glGenBuffers(1, &_vertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
        // Now we are populating it with some data
        // -0.5 is a quarter of the way from left side of the screen
        // 0.5f is the other (right) side of the window.
        // {x, y, z}
        float vertices[3*3] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.f,
            0.0f, 0.5f, 0.0f
        };

        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // Telling OpenGL the layout of our buffer.
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr); // provind a vertex a shader


        // Creating index buffer
        // element buffer and index buffers are the same thing people referred to them as element buffer
        // - Buffer of indices of index into this buffer
        // - tell what order of where to draw these vertices.
        // - Kind of like into an index into an array.
        glGenBuffers(1, &_indexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);

        unsigned int indices[3] = {0, 1, 2};
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
			}
		)";

        _shader.reset(new Shader(vertexSrc, fragmentSrc));
    }

    Application::~Application(){}

    void Application::pushLayer(Layer* layer){
        _layerStack.pushLayer(layer);
        layer->onAttach();
    }

    void Application::pushOverlay(Layer* layer){
        _layerStack.pushOverlay(layer);
        layer->onAttach();
    }


    void Application::onEvent(Event& event){
        EventDispatcher dispatcher(event);
        // In order for dispatcher to tell which event to execute, this is where that happens

        // NOTE
        // - Dispatcher checks the incoming type event is the same as the static type in the Dispatch function
        //  then we execute that specific callback corresponding to that event.
        auto bind_function = [](auto* instance, auto member_function){
            return [instance, member_function](auto&& arg1){
                return (instance->*member_function)(std::forward<decltype(arg1)>(arg1));
            };
        };
        dispatcher.Dispatch<WindowCloseEvent>(bind_function(this, &Application::onWindowClose));

        // Iterating backwards thhrough the layer stack and thhen we called onEvent, and if it isn;t handled thhen it breaks 
        // If not a layer and an overlay then we do not continue.
        auto iter = _layerStack.end();
        while(iter != _layerStack.begin()){
            (*--iter)->onEvent(event);

            if(event._handled) break;
        }

    }


    void Application::Run(){
        while(isRunning){
            glClearColor(0.1f, 0.1f, 0.1f, 1);
            glClear(GL_COLOR_BUFFER_BIT);

            _shader->bind();
			glBindVertexArray(_vertexArr);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

            for(Layer* layer : _layerStack){
                layer->onUpdate();
            }

            _imguiLayer->begin();
            for(Layer* layer : _layerStack){
                layer->onImguiRender();
            }
            _imguiLayer->end();

            _window->onUpdate();
        }
    }

    bool Application::onWindowClose(WindowCloseEvent& e){
        isRunning = false;
        return true;
    }
};
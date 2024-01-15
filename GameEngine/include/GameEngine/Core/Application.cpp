#include <GameEngine/Core/Application.h>
#include <GameEngine/Core/EngineLogger.h>
#include <GameEngine/Events/ApplicationEvent.h>
#include <GameEngine/Renderer/Renderer.h>


namespace RendererEngine{
    Application* Application::_instance = nullptr;
    
    Application::Application(const std::string& name){
		RENDER_PROFILE_FUNCTION();

        render_core_assert(!_instance, "Application already exists!");
        isRunning = true;
		isMinimized = false;
        _instance = this;
        _window = std::unique_ptr<Window>(Window::create(name));

        _window->setEventCallback(bind_function(this, &Application::onEvent));

        // Initializing our renderer
        Renderer::init();

        _imguiLayer = new ImGuiLayer();
        pushOverlay(_imguiLayer);

    }

    Application::~Application(){
		RENDER_PROFILE_FUNCTION();
		// Renderer::shutdown(); // Add this	
	}

    void Application::pushLayer(Layer* layer){
		RENDER_PROFILE_FUNCTION();
        _layerStack.pushLayer(layer);
        layer->onAttach();
    }

    void Application::pushOverlay(Layer* layer){
		RENDER_PROFILE_FUNCTION();
        _layerStack.pushOverlay(layer);
        layer->onAttach();
    }


    void Application::onEvent(Event& event){
		RENDER_PROFILE_FUNCTION();
        EventDispatcher dispatcher(event);
        // In order for dispatcher to tell which event to execute, this is where that happens

        // NOTE
        // - Dispatcher checks the incoming type event is the same as the static type in the Dispatch function
        //  then we execute that specific callback corresponding to that event.
        dispatcher.Dispatch<WindowCloseEvent>(bind_function(this, &Application::onWindowClose));
        dispatcher.Dispatch<WindowResizeEvent>(bind_function(this, &Application::onWindowResize));

        // Iterating backwards thhrough the layer stack and thhen we called onEvent, and if it isn;t handled thhen it breaks 
        // If not a layer and an overlay then we do not continue.
        auto iter = _layerStack.end();
        while(iter != _layerStack.begin()){
            (*--iter)->onEvent(event);

            if(event._handled) break;
        }

    }


    void Application::Run(){
		RENDER_PROFILE_SCOPE("Runloop");

        while(isRunning){
			RENDER_PROFILE_SCOPE("Run Mainloop");
            // Is going to be showing how lonmg this frame current time and the last frame time
            float time = (float)glfwGetTime(); // Should be in platform::getTime() (containing impl for Mac, Windows, etc.)
            Timestep timestep = time - _lastFrameTime;
            _lastFrameTime = time;
			
			if(!isMinimized){
				{
				RENDER_PROFILE_SCOPE("LayerStack onUpdate in run");
				for(Layer* layer : _layerStack){
				    layer->onUpdate(timestep);
				}
				}

				_imguiLayer->begin();
				{
				RENDER_PROFILE_SCOPE("LayerStack onImguiRender in Application::run()");
				for(Layer* layer : _layerStack){
				    layer->onImguiRender();
				}
				}
				_imguiLayer->end();
			}

            _window->onUpdate();
        }
    }
	
	void Application::close(){
		isRunning = false;
	}

    bool Application::onWindowClose(WindowCloseEvent& e){
        isRunning = false;
        return true;
    }

	bool Application::onWindowResize(WindowResizeEvent& e){
			RENDER_PROFILE_FUNCTION();
		if(e.GetWidth() == 0 || e.GetHeight() == 0){
			isMinimized = true;
			coreLogInfo("True said here!");
			return false;
		}

		// Telling the renderer the frame buffer has been resized
		isMinimized = false;
		Renderer::onWindowResize(e.GetWidth(), e.GetHeight());
		return false;
	}
};

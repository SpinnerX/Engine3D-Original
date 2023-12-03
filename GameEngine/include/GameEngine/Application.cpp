#include "Application.h"
#include <GameEngine/Renderer/Renderer.h>
#include <GameEngine/platforms/Windows/WindowsInput.h>

namespace RendererEngine{
    Application* Application::_instance = nullptr;
    
    Application::Application(){

        render_core_assert(!_instance, "Application already exists!");
        isRunning = true;
        _instance = this;
        _window = std::unique_ptr<Window>(Window::create());

        _window->setEventCallback(bind_function(this, &Application::onEvent));

        // Initializing our renderer
        Renderer::init();

        _imguiLayer = new ImGuiLayer();
        pushOverlay(_imguiLayer);

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
            // Is going to be showing how lonmg this frame current time and the last frame time
            float time = (float)glfwGetTime(); // Should be in platform::getTime() (containing impl for Mac, Windows, etc.)
            Timestep timestep = time - _lastFrameTime;
            _lastFrameTime = time;

            for(Layer* layer : _layerStack){
                layer->onUpdate(timestep);
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
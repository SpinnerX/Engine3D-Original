#include "Application.h"
#include <GameEngine/Events/ApplicationEvent.h>
#include <GameEngine/EngineLogger.h>

namespace RendererEngine{
    Application::Application(){
        _window = std::unique_ptr<Window>(Window::create());
        isRunning = true;
    }

    Application::~Application(){}


    void Application::Run(){
        while(isRunning){
            _window->onUpdate();

        }
    }
};
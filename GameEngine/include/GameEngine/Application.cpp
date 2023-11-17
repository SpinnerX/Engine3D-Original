#include "Application.h"
#include <GameEngine/Events/ApplicationEvent.h>
#include <GLFW/glfw3.h>
#include <fmt/ostream.h>

namespace RendererEngine{
    #define bind_event_function(x) std::bind(&Application::x, this, std::placeholders::_1)
    // template<typename T>
    // Window::EventCallbackFn bind_event_function(T x) {
    //     return std::bind(&x, this, std::placeholders::_1);
    // }
    Application::Application(){
        _window = std::unique_ptr<Window>(Window::create());
        // _window.setEventCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));
        _window->setEventCallback(bind_event_function(onEvent));
        isRunning = true;
    }

    Application::~Application(){}

    void Application::onEvent(Event& event){
        coreLogTrace("{}", fmt::streamed(event));
    }


    void Application::Run(){
        while(isRunning){
            glClearColor(1, 0, 1, 1);
            glClear(GL_COLOR_BUFFER_BIT);
            _window->onUpdate();

        }
    }
};
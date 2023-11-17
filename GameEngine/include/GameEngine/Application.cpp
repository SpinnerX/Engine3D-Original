#include "Application.h"
#include <GLFW/glfw3.h>

namespace RendererEngine{
    // std::bind is how we tell which Application function we want to bind 
    // #define bind_event_function(x) std::bind(&Application::x, this, std::placeholders::_1)

    // template<typename function>
    // void bind_event_function(){
    //     std::bind(&Application::function, this, std::placeholders::_1);
    // }


    /**
     * 
     * @brief
     * 
     * T: class instance (such as the class instance like "this" keyword)
     * M: is the function we are forwarding a callable object
     * 
    */
    template<typename T>
    auto bind_event_function(T* instance, auto M){
        return std::bind(M, instance, std::placeholders::_1);
    }


    // template<typename T>
    // Window::EventCallbackFn bind_event_function(T x) {
    //     return std::bind(&x, this, std::placeholders::_1);
    // }
    Application::Application(){
        _window = std::unique_ptr<Window>(Window::create());
        // _window.setEventCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));
        // _window->setEventCallback(bind_event_function(onEvent));

        // _window->setEventCallback(bind_event_function(this, &Application::onEvent));

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

        isRunning = true;
    }

    Application::~Application(){}

    void Application::onEvent(Event& event){
        EventDispatcher dispatcher(event);

        // auto bind_function = [&](){
        //     onWindowClose();
        // };

        // In order for dispatcher to tell which event to execute, this is where that happens

        // NOTE
        // - Dispatcher checks the incoming type event is the same as the static type in the Dispatch function
        //  then we execute that specific callback corresponding to that event.
        // dispatcher.Dispatch<WindowCloseEvent>(bind_event_function(onWindowClose));
        // dispatcher.Dispatch<WindowCloseEvent>(bind_event_function(this, &Application::onWindowClose));
        auto bind_function = [](auto* instance, auto member_function){
            return [instance, member_function](auto&& arg1){
                return (instance->*member_function)(std::forward<decltype(arg1)>(arg1));
            };
        };
        dispatcher.Dispatch<WindowCloseEvent>(bind_function(this, &Application::onWindowClose));
        coreLogTrace("{}", event);

    }


    void Application::Run(){
        while(isRunning){
            glClearColor(1, 0, 1, 1);
            glClear(GL_COLOR_BUFFER_BIT);
            _window->onUpdate();
        }
    }

    bool Application::onWindowClose(WindowCloseEvent& e){
        isRunning = false;
        return true;   
    }
};
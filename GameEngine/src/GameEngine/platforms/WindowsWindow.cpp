#include <GameEngine/platforms/WindowsWindow.h>
#include <GameEngine/EngineLogger.h>

namespace RendererEngine{
    static bool _glfwInitialized = false;

    Window* Window::create(const WindowProps& props){
        // return new WindowsWindow(props);
        // return std::make_unique<WindowsWindow>();
        return new WindowsWindow(props);
    }

    WindowsWindow::WindowsWindow(const WindowProps& props){
        init(props);
    }

    WindowsWindow::~WindowsWindow(){
        shutdown();
    }

    void WindowsWindow::init(const WindowProps& props){
        _data.title = props.title;
        _data.width = props.width;
        _data.height = props.height;

        // Logging in window data being passed into this function
        coreLogInfo("Creating Window {}: ({}, {})", props.title, props.width, props.height);

        // // We should check if GLFW is initialized before proceeding
        if(!_glfwInitialized){
            // TODO: glfwTerminate on system shutfown
            int success = glfwInit();
            render_core_assert(success, "Could not initialize GLFW!"); // Chhecking if glfw initialized successfully and then set that variable to true
            _glfwInitialized = true;
        }

        _window = glfwCreateWindow((int)props.width, (int)props.height, _data.title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(_window); // Basically making this current window our context window
        glfwSetWindowUserPointer(_window, &_data);
        setVSync(true);
    }

    void WindowsWindow::shutdown(){
        glfwDestroyWindow(_window);
    }

    void WindowsWindow::onUpdate(){
        glfwPollEvents();
        glfwSwapBuffers(_window);
    }

    void WindowsWindow::setVSync(bool enabled){
        // we are chhecking if we'd like to enable vsync.
        if(enabled){
            glfwSwapInterval(1);
        }
        else{
            glfwSwapInterval(0);
        }

        _data.vSync = true;
    }

    // bool WindowsWindow::isVSync(){
    //     return _data.vSync;
    // }




};
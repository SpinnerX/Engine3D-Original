#pragma once
#include <GameEngine/core.h>
#include <GameEngine/Window.h>

namespace RendererEngine{
    class RENDER_API Application{
    public:
        Application();
        ~Application();

        void Run();

    private:
        std::unique_ptr<Window> _window; // a unique pointer because this class owns this ptr
        bool isRunning;
    };

    // To be defined in client.
    Application* CreateApplication();
};
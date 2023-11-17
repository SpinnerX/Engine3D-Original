#pragma once
#include <GameEngine/core.h>
#include <GameEngine/Window.h>

namespace RendererEngine{
    class RENDER_API Application{
    public:
        Application();
        ~Application();

        void Run();

        // We can use the EventDispatcher created to dispatch events depending on what kind of
        // events that is needed to dispatched being passed in.
        void onEvent(Event& event);

    private:
        std::unique_ptr<Window> _window; // a unique pointer because this class owns this ptr
        bool isRunning;
    };

    // To be defined in client.
    Application* CreateApplication();
};
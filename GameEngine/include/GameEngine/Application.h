#pragma once
#include <GameEngine/core.h>

namespace RendererEngine{
    class RENDER_API Application{
    public:
        Application();
        ~Application();

        void Run();
    };

    // To be defined in client.
    Application* CreateApplication();
};
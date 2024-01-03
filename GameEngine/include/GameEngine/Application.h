#pragma once
#include "Events/ApplicationEvent.h"
#include <memory>
#include <GameEngine/core.h>
#include <GameEngine/Window.h>
#include <GameEngine/LayerStack.h>
#include <GameEngine/Imgui/ImGuiLayer.h>
#include <GameEngine/Core/Timestep.h>

namespace RendererEngine{
    // Application
    // - Essentially how users will run their own applications
    class Application{
    public:
        Application();
        ~Application();

        void Run();

        // We can use the EventDispatcher created to dispatch events depending on what kind of
        // events that is needed to dispatched being passed in.
        void onEvent(Event& event);

        void pushLayer(Layer* layer);
        void pushOverlay(Layer* layer);

        // Wherever we are in our codebase, we will want to access the application
        // since this application contain important informaiton
        // Therefore why we only create one instance.
        inline static Application& Get() { return *_instance; }
        inline Window& GetWindow() { return *_window; }

    private:
        bool onWindowClose(WindowCloseEvent& e);
        bool onWindowResize(WindowResizeEvent& e);

    private:
        std::unique_ptr<Window> _window; // a unique pointer because this class owns this ptr
        ImGuiLayer* _imguiLayer; // ImGuiLayer class (this class owns this ptr)
        bool isRunning;
		bool isMinimized;
        LayerStack _layerStack;

        float _lastFrameTime = 0.0f; // Time it took to render the last frame
    private:
        // Since there really is only going to be one application
        static Application* _instance; // Getting our current application instance
    };

    // To be defined in client.
    Application* CreateApplication();
};

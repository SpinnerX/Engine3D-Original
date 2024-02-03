#pragma once
#include <memory>
#include <GameEngine/Core/core.h>
#include <GameEngine/Core/Window.h>
#include <GameEngine/Core/LayerStack.h>
#include <GameEngine/Imgui/ImGuiLayer.h>
#include <GameEngine/Core/Timestep.h>

namespace RendererEngine{
	struct ApplicationCommandLineArgs{
		int count = 0;
		char** args = nullptr;

		const char* operator[](int index) const {
			assert(index < count);
			return args[index];
		}
	};

    // Application
    // - Essentially how users will run their own applications
    class Application{
    public:
        /* Application(const std::string& name="Game Engine"); */
		Application(const std::string& name="Game Engine", ApplicationCommandLineArgs args = ApplicationCommandLineArgs{});
        ~Application();

        void Run();

        // We can use the EventDispatcher created to dispatch events depending on what kind of
        // events that is needed to dispatched being passed in.
        void onEvent(Event& event);

        void pushLayer(Layer* layer);
        void pushOverlay(Layer* layer);
		
		void close();
		
		ImGuiLayer* getImGuiLayer() { return _imguiLayer; }

        // Wherever we are in our codebase, we will want to access the application
        // since this application contain important informaiton
        // Therefore why we only create one instance.
        inline static Application& Get() { return *_instance; }
        inline Window& GetWindow() { return *_window; }

		ApplicationCommandLineArgs getCommandLineArgs() const { return _commandLineArgs; }

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
		ApplicationCommandLineArgs _commandLineArgs;
    private:
        // Since there really is only going to be one application
        static Application* _instance; // Getting our current application instance
    };

    // To be defined in client.
    Application* CreateApplication(ApplicationCommandLineArgs args);
};

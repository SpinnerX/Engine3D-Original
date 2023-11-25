#pragma once
#include <memory>
#include <GameEngine/core.h>
#include <GameEngine/Window.h>
#include <GameEngine/LayerStack.h>
#include <GameEngine/Imgui/ImGuiLayer.h>
#include <GameEngine/Renderer/Shader.h>
#include <GameEngine/Renderer/Buffer.h>

namespace RendererEngine{
    class RENDER_API Application{
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

    private:
        std::unique_ptr<Window> _window; // a unique pointer because this class owns this ptr
        ImGuiLayer* _imguiLayer; // ImGuiLayer class (this class owns this ptr)
        bool isRunning;
        LayerStack _layerStack;

        // These unsigned integers are going to represent the ID's
        unsigned int _vertexArr;

        std::unique_ptr<Shader> _shader;
        std::unique_ptr<VertexBuffer> _vertexBuffer;
        std::unique_ptr<IndexBuffer> _indexBuffer;

        unsigned _testVertBuffer, _testIndexBuffer;
    private:
        // Since there really is only going to be one application
        static Application* _instance; // Getting our current application instance
    };

    // To be defined in client.
    Application* CreateApplication();
};
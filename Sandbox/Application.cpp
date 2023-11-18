#include <GameEngine/GameEngine.h>

// This is just an example on how to make a layer
class ExampleLayer : public RendererEngine::Layer{
public:
    ExampleLayer() : Layer("Example"){}

    void onUpdate() override {
        clientLogInfo("ExampleLayer::Update");
    }

    void onEvent(RendererEngine::Event& event) override{
        clientLogTrace("{}", event);
    }
};

class Sandbox : public RendererEngine::Application{
public:
    Sandbox() {
        pushLayer(new ExampleLayer());
    }

    ~Sandbox() {}
};

RendererEngine::Application* RendererEngine::CreateApplication(){
    return new Sandbox();
}
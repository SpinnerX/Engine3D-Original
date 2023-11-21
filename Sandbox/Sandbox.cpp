#include <GameEngine/GameEngine.h>

// This is just an example on how to make a layer
class ExampleLayer : public RendererEngine::Layer{
public:
    ExampleLayer() : Layer("Example"){}

    void onUpdate() override {
        clientLogInfo("ExampleLayer::Update");

        if(RendererEngine::InputPoll::isKeyPressed(RENDER_KEY_TAB)){
            clientLogTrace("Tab key has been pressed!\n");
        }
    }

    void onEvent(RendererEngine::Event& event) override{
        clientLogTrace("{}", event);
        if(event.GetEventType() == RendererEngine::EventType::KeyPressed){
            RendererEngine::KeyPressedEvent& e = (RendererEngine::KeyPressedEvent&)event;
            clientLogTrace("{}\n", (char)e.GetKeyCode());
            // clientLogTrace("{}", event);
        }
    }
};

class Sandbox : public RendererEngine::Application{
public:
    Sandbox() {
        pushLayer(new ExampleLayer());
        pushOverlay(new RendererEngine::ImGuiLayer());
    }

    ~Sandbox() {}
};

RendererEngine::Application* RendererEngine::CreateApplication(){
    return new Sandbox();
}
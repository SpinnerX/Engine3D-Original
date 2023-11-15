#include <GameEngine/GameEngine.h>

class Sandbox : public RendererEngine::Application{
public:
    Sandbox() {}
    ~Sandbox() {}
};

RendererEngine::Application* RendererEngine::CreateApplication(){
    return new Sandbox();
}
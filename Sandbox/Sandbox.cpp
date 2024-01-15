#include "Sandbox2D.h"
#include <GameEngine/Core/EntryPoint.h>

class Sandbox : public RendererEngine::Application{
public:
    Sandbox() : RendererEngine::Application("Some Game Engine") {
		pushLayer(new Sandbox2D());
    }

    ~Sandbox() {}
};

RendererEngine::Application* RendererEngine::CreateApplication(){
    return new Sandbox();
}

#include "GameLayer.h"
#include <GameEngine/Core/EntryPoint.h>

class Game2D : public RendererEngine::Application{
public:
	Game2D() : Application() {
		pushLayer(new GameLayer());
	}

	~Game2D(){}
};


RendererEngine::Application* RendererEngine::CreateApplication(RendererEngine::ApplicationCommandLineArgs args){
	return new Game2D();
}

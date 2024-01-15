#include <GameEngine/Core/GameEngine.h>
#include <GameEngine/Core/EntryPoint.h>
#include "EditorLayer.h"


namespace RendererEngine{
	class EngineEditor : public Application{
	public:
		EngineEditor() : Application("Engine Editor") {
			pushLayer(new EditorLayer());
		}

		~EngineEditor(){}
	};

	Application* CreateApplication(){
		return new EngineEditor();
	}
};

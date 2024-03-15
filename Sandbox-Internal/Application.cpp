#include <Engine3D/Core/Application.h>
#include <Engine3D/Core/EntryPoint.h>
#include "ExampleLayer3D.h"


class Application : public Engine3D::Application{
public:
	Application() : Engine3D::Application() {}
};




Engine3D::Application* Engine3D::CreateApplication(Engine3D::ApplicationCommandLineArgs args){
	return new Application();
}

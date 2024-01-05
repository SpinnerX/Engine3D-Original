#include "Sandbox2D.h"
#include "Renderer/Renderer2D.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GameEngine/platforms/OpenGL/OpenGLShader.h>

// It would be better to use a lambda without constructing a std::function
// Because a lambda will actually generate a type that is unique to this lambda, which is why there is a use for templates or auto to handle that
template<typename Fn>
class Timer{
public:

	Timer(const char* n, Fn&& function) : _name(n), _function(function), _stopped(false){
		// Starting the Timer
		_startTimePoint = std::chrono::high_resolution_clock::now();
	}

	~Timer(){
		if(!_stopped){
			stop();
		}
	}

	void stop(){

		// Recording out actual total time
		auto endTimePoint = std::chrono::high_resolution_clock::now();

		long long start = std::chrono::time_point_cast<std::chrono::microseconds>(_startTimePoint).time_since_epoch().count();
		long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).time_since_epoch().count();
		_stopped = true;
		
		float duration = (end - start) * 0.001f;
		_function({_name, duration});
	}

private:
	const char* _name;
	Fn _function;
	std::chrono::time_point<std::chrono::steady_clock> _startTimePoint;
	bool _stopped;
};

// NOTE: WiLL Be changing this as this is temporary
#define PROFILE_SCOPE(name) Timer timer##__LINE__(name, [&](ProfileResult profileResult) { _profileResults.push_back(profileResult); })
/* static void start(const char* name){ */
/* 	Timer timer(name [&](ProfileResult profileResult){ _profileResults.push_back(profileResult); }); */
/* } */

Sandbox2D::Sandbox2D() : Layer("Sandbox2D"), _cameraController(1280.0f / 720.0f){
}

void Sandbox2D::onAttach(){
	_checkerboardTexture = RendererEngine::Texture2D::Create("assets/Checkerboard.png");
}

void Sandbox2D::onDetach(){
}

void Sandbox2D::onUpdate(RendererEngine::Timestep ts){
	/* Timer timer("Sandbox2D::onUpdate", [&](auto profileResult){ _profileResults.push_back(profileResult); }); */
	PROFILE_SCOPE("Sandbox2D::onUpdate");
	
	// Update
	{
		/* Timer timer("CameraController::onUpdate", [&](auto profileResult) { _profileResults.push_back(profileResult); }); */
		PROFILE_SCOPE("CameraController::onUpdate");
		_cameraController.onUpdate(ts);
	}

	// Render
	{
		PROFILE_SCOPE("Renderer Prep");
		RendererEngine::RendererCommand::setClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		RendererEngine::RendererCommand::clear();
	}
	
	{
		PROFILE_SCOPE("Renderer Draw");
		RendererEngine::Renderer2D::beginScene(_cameraController.getCamera());
	
		// Our draw quads, for drawing our rectangles.
		RendererEngine::Renderer2D::drawQuad({-1.0f, 0.0f}, {0.8f, 0.8f}, {0.8f, 0.2f, 0.3f, 1.0f});
		RendererEngine::Renderer2D::drawQuad({0.5f, -0.5f}, {0.5f, 0.75f}, {0.2f, 0.3f, 0.8f, 1.0f});
		RendererEngine::Renderer2D::drawQuad({0.0f, 0.0f, -0.1f}, {10.0f, 10.0f}, _checkerboardTexture);
	
		RendererEngine::Renderer2D::endScene();
	}
}

void Sandbox2D::onImguiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(_squareColor));


	for(auto& result : _profileResults){
		char label[50];

		/* strncpy(label, fmt::format("{:.3f}ms is {}", result.time, result.name).c_str(), sizeof(label) - 1); */
		strcpy(label, fmt::format("{:.3f}ms is {}", result.time, result.name).c_str());
		
		ImGui::Text("%s", label);
	}

	_profileResults.clear();


	ImGui::End();
}

void Sandbox2D::onEvent(RendererEngine::Event& e)
{
	_cameraController.onEvent(e);
}



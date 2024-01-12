#include "Sandbox2D.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GameEngine/platforms/OpenGL/OpenGLShader.h>

Sandbox2D::Sandbox2D() : Layer("Sandbox2D"), _cameraController(1280.0f / 720.0f){
}

void Sandbox2D::onAttach(){
	RENDER_PROFILE_FUNCTION();
	_checkerboardTexture = RendererEngine::Texture2D::Create("assets/Checkerboard.png");
}

void Sandbox2D::onDetach(){
	RENDER_PROFILE_FUNCTION();
}

void Sandbox2D::onUpdate(RendererEngine::Timestep ts){
	/* Timer timer("Sandbox2D::onUpdate", [&](auto profileResult){ _profileResults.push_back(profileResult); }); */
	RENDER_PROFILE_FUNCTION();
	
	// Update
	/* Timer timer("CameraController::onUpdate", [&](auto profileResult) { _profileResults.push_back(profileResult); }); */
	_cameraController.onUpdate(ts);
	
	RendererEngine::Renderer2D::resetStats();

	// Render
	{
		RENDER_PROFILE_FUNCTION();
		RendererEngine::RendererCommand::setClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		RendererEngine::RendererCommand::clear();
	}
	
	{
		RENDER_PROFILE_FUNCTION();
		RendererEngine::Renderer2D::beginScene(_cameraController.getCamera());
		static float rotation = 0.0f;
		rotation += ts * 50.0f;


		// Our draw quads, for drawing our rectangles.
		RendererEngine::Renderer2D::drawRotatedQuad({1.0f, 0.0f}, {0.8f, 0.8f}, -45.0f, {0.8f, 0.2f, 0.3f, 1.0f}); // Red shape
		RendererEngine::Renderer2D::drawQuad({-1.0f, 0.0f}, {0.8f, 0.8f}, {0.8f, 0.2f, 0.3f, 1.0f}); // Red shape
		RendererEngine::Renderer2D::drawQuad({0.5f, -0.5f}, {0.5f, 0.75f}, {0.2f, 0.3f, 0.8f, 1.0f}); // blue shape
		RendererEngine::Renderer2D::drawQuad({0.0f, 0.0f, -0.1f}, {20.0f, 20.0f}, _checkerboardTexture, 10.0f); // checkerboard texture shape
		RendererEngine::Renderer2D::drawRotatedQuad({ -2.0f, 0.0f, 0.0f}, {1.0f, 1.0f}, rotation, _checkerboardTexture, 20.0f); // checkerboard texture shape
	
		RendererEngine::Renderer2D::endScene();

		RendererEngine::Renderer2D::beginScene(_cameraController.getCamera());

		for(float y = -5.0f; y < 5.0f; y += 0.5f){
			for(float x = -5.0f; x < 5.0f; x += 0.5f){

				glm::vec4 color = { (x + 0.5f) / 10.f, 0.4f, (y + 5.0f) / 10.0f, 0.7f};
				RendererEngine::Renderer2D::drawQuad({x, y}, {0.45f, 0.45f}, color);
			}
			
		}

		RendererEngine::Renderer2D::endScene();
	}
}

void Sandbox2D::onImguiRender(){
	ImGui::Begin("Settings");

	auto stats = RendererEngine::Renderer2D::getStats();
	ImGui::Text("Renderer2D Stats");
	ImGui::Text("Draw Calls %d", stats.drawCalls);
	ImGui::Text("Quads: %d", stats.quadCount);
	ImGui::Text("Vertices: %d", stats.getTotalVertexCount());
	ImGui::Text("Indices: %d", stats.getTotalIndexCount());

	ImGui::ColorEdit4("Square Color", glm::value_ptr(_squareColor));
	ImGui::End();
}

void Sandbox2D::onEvent(RendererEngine::Event& e){
	_cameraController.onEvent(e);
}



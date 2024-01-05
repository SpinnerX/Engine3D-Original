#include "Sandbox2D.h"
#include "Renderer/RenderCommand.h"
#include "Renderer/Renderer2D.h"
#include <imgui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GameEngine/platforms/OpenGL/OpenGLShader.h>

Sandbox2D::Sandbox2D() : Layer("Sandbox2D"), _cameraController(1280.0f / 720.0f){
}

void Sandbox2D::onAttach(){
	_checkerboardTexture = RendererEngine::Texture2D::Create("assets/Checkerboard.png");
}

void Sandbox2D::onDetach(){
}

void Sandbox2D::onUpdate(RendererEngine::Timestep ts){
	// Update
	_cameraController.onUpdate(ts);

	// Render
	RendererEngine::RendererCommand::setClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	RendererEngine::RendererCommand::clear();

	RendererEngine::Renderer2D::beginScene(_cameraController.getCamera());
	
	// Our draw quads, for drawing our rectangles.
	RendererEngine::Renderer2D::drawQuad({-1.0f, 0.0f}, {0.8f, 0.8f}, {0.8f, 0.2f, 0.3f, 1.0f});
	RendererEngine::Renderer2D::drawQuad({0.5f, -0.5f}, {0.5f, 0.75f}, {0.2f, 0.3f, 0.8f, 1.0f});
	RendererEngine::Renderer2D::drawQuad({0.0f, 0.0f, -0.1f}, {10.0f, 10.0f}, _checkerboardTexture);
	
	RendererEngine::Renderer2D::endScene();
}

void Sandbox2D::onImguiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(_squareColor));
	ImGui::End();
}

void Sandbox2D::onEvent(RendererEngine::Event& e)
{
	_cameraController.onEvent(e);
}



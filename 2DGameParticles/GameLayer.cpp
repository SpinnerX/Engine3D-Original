#include "GameLayer.h"

GameLayer::GameLayer() : Layer("GameLayer"), _cameraController(1280.0f / 720.0f){
}

void GameLayer::onAttach() {
	RENDER_PROFILE_FUNCTION();
	_checkerboardTexture = RendererEngine::Texture2D::Create("assets/Checkerboard.png");
		
	_particle.colorBegin = { 254 / 255.0f, 212 / 255.0f, 123 / 255.0f, 1.0f };
	_particle.colorEnd = { 254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f };
	_particle.sizeBegin = 0.5f, _particle.sizeVariation = 0.3f, _particle.sizeEnd = 0.0f;
	_particle.lifetime = 1.0f;
	_particle.velocity = { 0.0f, 0.0f };
	_particle.velocityVariation = { 3.0f, 1.0f };
	_particle.pos = { 0.0f, 0.0f };
}

void GameLayer::onDetach() {

}

void GameLayer::onUpdate(RendererEngine::Timestep ts) {
	RENDER_PROFILE_FUNCTION();
	RendererEngine::Renderer2D::resetStats();

	{
		RENDER_PROFILE_SCOPE("Renderer Prep");
		RendererEngine::RendererCommand::setClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		RendererEngine::RendererCommand::clear();
	}


	
	{
		static float rotation = 0.0f;
		rotation += ts * 50.0f;

		RENDER_PROFILE_SCOPE("Renderer Draw");
		RendererEngine::Renderer2D::beginScene(_cameraController.getCamera());

		RendererEngine::Renderer2D::drawRotatedQuad({1.0f, 0.0f}, {0.8f, 0.8f}, glm::radians(-45.0f), {0.8f, 0.2f, 0.3f, 1.0f}); // Red shape
		RendererEngine::Renderer2D::drawQuad({-1.0f, 0.0f}, {0.8f, 0.8f}, {0.8f, 0.2f, 0.3f, 1.0f}); // Red shape
		RendererEngine::Renderer2D::drawQuad({0.5f, -0.5f}, {0.5f, 0.75f}, {0.2f, 0.3f, 0.8f, 1.0f}); // blue shape
		RendererEngine::Renderer2D::drawQuad({0.0f, 0.0f, -0.1f}, {20.0f, 20.0f}, _checkerboardTexture, 10.0f); // checkerboard texture shape
		RendererEngine::Renderer2D::drawRotatedQuad({ -2.0f, 0.0f, 0.0f}, {1.0f, 1.0f}, glm::radians(rotation), _checkerboardTexture, 20.0f); // checkerboard texture shape
		
		RendererEngine::Renderer2D::endScene();
	}



	RendererEngine::Renderer2D::beginScene(_cameraController.getCamera());

	for(float y = -5.0f; y < 5.0f; y += 0.5f){
		for(float x = -5.0f; x < 5.0f; x += 0.5f){
			glm::vec4 color = { (x + 0.5f) / 10.f, 0.4f, (y + 5.0f) / 10.0f, 0.7f};
			RendererEngine::Renderer2D::drawQuad({x, y}, {0.45f, 0.45f}, color);
		}
	}

	RendererEngine::Renderer2D::endScene();




	if(RendererEngine::InputPoll::isMouseButtonPressed(RENDER_MOUSE_BUTTON_LEFT)){
		auto [x, y] = RendererEngine::InputPoll::getMousePosition();
		auto w = RendererEngine::Application::Get().GetWindow().getWidth();
		auto h = RendererEngine::Application::Get().GetWindow().getHeight();

		auto bounds = _cameraController.getBounds();
		auto pos = _cameraController.getCamera().getPosition();
		x = (x/w) * bounds.getWidth() - bounds.getWidth() * 0.5f;
		y = bounds.getHeight() * 0.5f - (y / h) * bounds.getHeight();

		_particle.pos = {x + pos.x, y+pos.x};

		for(int i = 0; i < 5; i++)
			_particleSystem.emit(_particle);
	}

	_particleSystem.onUpdate(ts);
	_particleSystem.onRender(_cameraController.getCamera());

}

void GameLayer::onImguiRender(){
	ImGui::Begin("Settings");

	auto stats = RendererEngine::Renderer2D::getStats();
	ImGui::Text("Renderer2D Stats");
	ImGui::Text("Draw Calls %d", stats.drawCalls);
	ImGui::Text("Quads: %d", stats.quadCount);
	ImGui::Text("Vertices: %d", stats.getTotalVertexCount());
	ImGui::Text("Indices: %d", stats.getTotalIndexCount());

	ImGui::End();
}

void GameLayer::onEvent(RendererEngine::Event& e) {
	_cameraController.onEvent(e);
}

#pragma once
#include <GameEngine/Core/GameEngine.h>

/*
 *
 * Sandbox2D
 * - Helps prepare on what is needed in regards to our 2D Renderer
 *
 *
*/

class Sandbox2D : public RendererEngine::Layer{
public:
	Sandbox2D();
	
	virtual ~Sandbox2D() = default;

	virtual void onAttach() override;
	virtual void onDetach() override;

	virtual void onUpdate(RendererEngine::Timestep ts) override;

	virtual void onImguiRender() override;

	virtual void onEvent(RendererEngine::Event& e) override;

private:
	RendererEngine::OrthographicCameraController _cameraController;

	// This'll be temporary only!
	RendererEngine::Ref<RendererEngine::VertexArray> _squareVertexArrays;
	RendererEngine::Ref<RendererEngine::Shader> _flatColorShader;

	RendererEngine::Ref<RendererEngine::Texture2D> _checkerboardTexture;

	// Act as our result of different profiles that we want to manage
	struct ProfileResult{
		const char* name;
		float time;
	};

	std::vector<ProfileResult> _profileResults;

	glm::vec4 _squareColor = {0.2f, 0.3f, 0.8, 1.0f};
};

#pragma once
#include "ParticleSystem.h"


class GameLayer : public RendererEngine::Layer{
public:
	GameLayer();
	virtual ~GameLayer() = default;
	virtual void onAttach() override;
	virtual void onDetach() override;

	void onUpdate(RendererEngine::Timestep ts) override;

	virtual void onImguiRender() override;

	void onEvent(RendererEngine::Event& e) override;


private:
	RendererEngine::OrthographicCameraController _cameraController;
	RendererEngine::Ref<RendererEngine::VertexArray> _squareVA;
	RendererEngine::Ref<RendererEngine::Shader> _flatColotShader;

	RendererEngine::Ref<RendererEngine::Texture2D> _checkerboardTexture;
	RendererEngine::Ref<RendererEngine::Texture2D> _spriteSheet;
	RendererEngine::Ref<RendererEngine::SubTexture2D> _textureStairs;
	RendererEngine::Ref<RendererEngine::SubTexture2D> _textureBarrel;
	RendererEngine::Ref<RendererEngine::SubTexture2D> _textureTree;

	glm::vec4 color = {0.2f, 0.3f, 0.8f, 1.0f};

	particleSystem _particleSystem;
	particleProps _particle;
	uint32_t _mapWidth;
	uint32_t _mapHeight;
	std::unordered_map<char, RendererEngine::Ref<RendererEngine::SubTexture2D> > _textureMap;
};

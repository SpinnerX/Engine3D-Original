#pragma once
#include "Renderer/OrthographicCamera.h"
#include "Renderer/Texture.h"

namespace RendererEngine{

	class Renderer2D{
	public:	
		static void Init();
		static void Shutdown();

		static void beginScene(const OrthographicCamera& camera);
		static void endScene();

		// primitives
		
		// TODO: Potentially use glm::vec3 to sort, by utilizing that z and modifying that value.
		//		 Setting that z values
		static void drawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color);
		static void drawQuad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color);
		static void drawQuad(const glm::vec2& pos, const glm::vec2& size, const Ref<Texture2D>& texture);
		static void drawQuad(const glm::vec3& pos, const glm::vec2& size, const Ref<Texture2D>& texture);
	};

};

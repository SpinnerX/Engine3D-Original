#pragma once
#include <GameEngine/Renderer/OrthographicCamera.h>
#include <GameEngine/Renderer/Texture.h>

namespace RendererEngine{

	class Renderer2D{
	public:	
		static void Init();
		static void Shutdown();

		static void beginScene(const OrthographicCamera& camera);
		static void endScene();

		/*
		 * Small NOTE: These are drawQuads for colors and textures.
		 * drawQuad
		 * @params
		 * @pos = position of the objects
		 * @size = scaling the size of objects
		 * @color = colorizing specific rgba channels to a specific color
		 * @rotation = specifying in glm::radians(angle) how much to rotate
		 * @tilingFactor = is the offset for how many tiles can be rendered via GPU
		 * @tintColor = sets the rgba channels value for specifying the color to tint that object
		 *
		*/
		static void drawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color);
		static void drawQuad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color);
		static void drawQuad(const glm::vec2& pos, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor=1.0f, const glm::vec4& tintColor=glm::vec4(1.0f));
		static void drawQuad(const glm::vec3& pos, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor=1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));

		static void drawRotatedQuad(const glm::vec2& pos, const glm::vec2& size, float rotation, const glm::vec4& color);
		static void drawRotatedQuad(const glm::vec3& pos, const glm::vec2& size, float rotation, const glm::vec4& color);
		static void drawRotatedQuad(const glm::vec2& pos, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor=1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
		static void drawRotatedQuad(const glm::vec3& pos, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor=1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
	};

};

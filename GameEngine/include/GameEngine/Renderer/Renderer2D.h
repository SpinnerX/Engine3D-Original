#pragma once
#include <GameEngine/Renderer/OrthographicCamera.h>
#include <GameEngine/Renderer/Camera.h> // TODO: May need to remove this..
#include <GameEngine/Renderer/Texture.h>
#include <GameEngine/Renderer/SubTexture2D.h>
#include <GameEngine/Renderer/EditorCamera.h>
namespace RendererEngine{

	class Renderer2D{
	public:

		struct RenderCamera{
			glm::mat4 projection;
			glm::mat4 view;
		};

		static void Init();
		static void Shutdown();

		static void beginScene(const Camera& camera, const glm::mat4& transform); // TODO: Remove
		static void beginScene(const EditorCamera& camera);
		static void beginScene(const OrthographicCamera& camera);

		static void endScene();

		static void flush();

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
		 *
		 * QUICK NOTE: Rotations is in radians.
		 *
		*/
		static void drawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color);
		static void drawQuad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color);
		static void drawQuad(const glm::vec2& pos, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor=1.0f, const glm::vec4& tintColor=glm::vec4(1.0f));
		static void drawQuad(const glm::vec3& pos, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor=1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
		static void drawQuad(const glm::vec2& pos, const glm::vec2& size, const Ref<SubTexture2D>& texture, float tilingFactor=1.0f, const glm::vec4& tintColor=glm::vec4(1.0f));
		static void drawQuad(const glm::vec3& pos, const glm::vec2& size, const Ref<SubTexture2D>& texture, float tilingFactor=1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));

		static void drawQuad(const glm::mat4& transform, const glm::vec4& color);
		static void drawQuad(const glm::mat4& transform, const Ref<Texture2D>& texture, float tilingFactor=1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));


		static void drawRotatedQuad(const glm::vec2& pos, const glm::vec2& size, float rotation, const glm::vec4& color);
		static void drawRotatedQuad(const glm::vec3& pos, const glm::vec2& size, float rotation, const glm::vec4& color);
		static void drawRotatedQuad(const glm::vec2& pos, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor=1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
		static void drawRotatedQuad(const glm::vec3& pos, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor=1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
		
		static void drawRotatedQuad(const glm::vec2& pos, const glm::vec2& size, float rotation, const Ref<SubTexture2D>& texture, float tilingFactor=1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
		static void drawRotatedQuad(const glm::vec3& pos, const glm::vec2& size, float rotation, const Ref<SubTexture2D>& texture, float tilingFactor=1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));

		// Allowing to control with our constant values
		// Such as allowing to modify in real time with these constant values.
		// How to know measuring, is through draw calls
		// They are resettable by client, when client resets the stats
		// This is up to the client for resetting
		struct Statistics{
			uint32_t drawCalls = 0; // number of draw calls
			uint32_t quadCount = 0;

			uint32_t getTotalVertexCount() { return quadCount * 4; }
			uint32_t getTotalIndexCount() { return quadCount * 6; }
		};

		static Statistics getStats();
		static void resetStats();
	private:
		static void flushAndReset();
	};

};

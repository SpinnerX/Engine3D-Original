#pragma once
#include <GameEngine/Renderer/OrthographicCamera.h>
#include <GameEngine/Renderer/Camera.h>

namespace RendererEngine{
	
	struct TagComponent{
		std::string tag;

		TagComponent() = default;
		TagComponent(const std::string& t) : tag(t){}
		TagComponent(const TagComponent&) = default;
	};

	struct TransformComponent{
		glm::mat4 transform = glm::mat4(1.0f);
		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::mat4& transform) : transform(transform) {}
			
		operator glm::mat4&() { return transform; }
		operator const glm::mat4&() const { return transform; }


	};

	struct SpriteRendererComponent{
		glm::vec4 color = {1.0f, 1.0f, 1.0f, 1.0f};

		SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent&) = default;
		SpriteRendererComponent(const glm::vec4& color) : color(color){}
	};
	
	/*
	 * Camera Component
	 * - Editor would not have a component itself.
	 * - Rather that the camera would be a component with an entity.
	 *
	 *
	 * */
	struct CameraComponent{

		Camera camera;

		// TODOL moving to scene.
		bool isPrimary = true; // this allows to see if this current camera is your primary camera.

		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
		CameraComponent(const glm::mat4& projecMat) : camera(projecMat){}
	};
};

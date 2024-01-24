#pragma once
#include <GameEngine/Renderer/OrthographicCamera.h>
#include <GameEngine/Scene/SceneCamera.h>
#include <GameEngine/Scene/ScriptableEntity.h>
#include <glm/gtc/matrix_transform.hpp>

namespace RendererEngine{
	
	struct TagComponent{
		std::string tag;

		TagComponent() = default;
		TagComponent(const std::string& t) : tag(t){}
		TagComponent(const TagComponent&) = default;
	};

	struct TransformComponent{
		/* glm::mat4 transform = glm::mat4(1.0f); */
		glm::vec3 translation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 rotation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 scale = { 1.0f, 1.0f, 1.0f };

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::vec3& t) : translation(t) {}
			
		glm::mat4 getTransform() const {
			glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), rotation.x, {1, 0, 0})
								 * glm::rotate(glm::mat4(1.0f), rotation.y, {0, 1, 0})
								 * glm::rotate(glm::mat4(1.0f), rotation.z, {0, 0, 1});

			return glm::translate(glm::mat4(1.0f), translation)
				   *  rotate
				   *  glm::scale(glm::mat4(1.0f), scale);
		}
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
	 * Quick NOTE
	 * - There are two types of camera in your scenes.
	 * - During game runtime, you can divide cams in two different cameras.
	 *		0.) Cameras that essentially should be rendering some kind of view of the scene, directly tied to render output to our viewport.
	 *			- Like making a 1920x1080, you want the camera to fill your screen.
	 *			- Minimizing, making the window smaller, or somewhat modifying the window.
	 *		1.) Fixed aspect ratio
	 *		2.) non-fixed aspect ratio
	 *			- Main camera 
	 *
	 * */
	struct CameraComponent{

		SceneCamera camera;

		// TODOL moving to scene.
		bool isPrimary = true; // this allows to see if this current camera is your primary camera.
		bool fixedAspectRatio = false; // Can check if true in editor meaning that the aspect ratio is fixedd. (Meaning the aspect ratio wont be changed)

		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
	};

	struct NativeScriptComponent{
		ScriptableEntity* instance = nullptr;
		
		ScriptableEntity*(*instantiateScript)(); // Usage: Just instantiates to the type we are binding (equivalent to doing std::function<void(ScriptableEntity *)>; called instantiateScript.)
		
		/*
		 *
		 *
		 *	@note takes a ptr to itself.
		 *
		 * */
		void (*destroyScript)(NativeScriptComponent *); // Usage: Destroys instance we are binding.
		
		/*
		 *
		 * @note Create new instance of this particular passed being passed.
		 * @note Deletes that instance, setting it to nullptr.
		 */
		template<typename T>
		void bind(){
			instantiateScript = []() { return static_cast<ScriptableEntity *>(new T()); };
			destroyScript = [](NativeScriptComponent* nsc) { delete nsc; nsc=nullptr; };
		}
	};
};

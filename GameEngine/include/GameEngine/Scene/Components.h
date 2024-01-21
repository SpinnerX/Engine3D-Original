#pragma once
#include <GameEngine/Renderer/OrthographicCamera.h>
#include <GameEngine/Scene/SceneCamera.h>
#include <GameEngine/Scene/ScriptableEntity.h>

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
		
		std::function<void()> instantiateFun; // Usage: Just instantiates to the type we are binding
		std::function<void()> destroyInstanceFun; // Usage: Destroys instance we are binding.

		std::function<void(ScriptableEntity*)> onCreateFun; // Usage: Just instantiates to the type we are binding
		std::function<void(ScriptableEntity*)> onDestroy; // Usage: Destroys instance we are binding.
		std::function<void(ScriptableEntity*, Timestep)> onUpdateFun;
		template<typename T>
		void bind(){
			instantiateFun = [&]() { instance = new T(); };
			destroyInstanceFun = [&]() { delete (T *)instance; };

			// converting this onCreate into the specific types instance.
			// Gets instantiated, by setting up that instance
			onCreateFun = [](ScriptableEntity* instance){ ((T *)instance)->onCreate(); };
			onDestroy = [](ScriptableEntity* instance){ ((T *)instance)->onDestroy(); };
			onUpdateFun = [](ScriptableEntity* instance, Timestep ts){ ((T *)instance)->onUpdate(ts); };
		}

	};
};

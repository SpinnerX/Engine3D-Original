#pragma once
#include <Engine3D/Entt/entt.h>
#include <Engine3D/Core/Timestep.h>
#include <Engine3D/Renderer/Renderer2D.h>
#include <Engine3D/Renderer/EditorCamera.h>


class b2World;
namespace Engine3D{
	/*
	 *
	 * Scene
	 * @note Essentially a container that contains our entities.
	 * @note Setting the size before rendering.
	 * @note Make sure when adding new camera to scene, it gets that effect.
	 *
	 *
	 * */
	class Entity;
	class Scene{
	public:
		Scene();
		~Scene();
		
		// We should be able to create an entity into our screen.
		Entity createEntity(const std::string& name=std::string());
		void destroyEntity(Entity entity);

		// Runtime start and stop
		
		// @note for starting our physics simulation via runtime.
		void onRuntimeStart();
		void onRuntimeStop();

		// temporary
		entt::registry& reg() { return _registry; }

		void onUpdateEditor(Timestep ts, EditorCamera& camera);
		void onUpdateRuntime(Timestep ts);

		void onViewportResize(uint32_t width, uint32_t height);

		Entity getPrimaryCamera();

	private:
		template<typename T>
		void onComponentAdded(Entity entity, T& component);
	private:
		entt::registry _registry; // entity used to determine which components belong together. registry contain the actual data.
		uint32_t _viewportWidth=0, _viewportHeight=0;

		b2World* _physicsWorld = nullptr;

		friend class Entity;
		friend class SceneSerializer;
		friend class SceneHeirachyPanel;
	};
};

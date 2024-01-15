#pragma once
#include <GameEngine/Entt/entt.h>
#include <GameEngine/Core/Timestep.h>
#include <GameEngine/Renderer/Renderer2D.h>

namespace RendererEngine{
	/*
	 *
	 * Scene
	 * - Essentially a container that contains our entities.
	 *
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

		// temporary
		entt::registry& reg() { return _registry; }

		void onUpdate(Timestep ts);

	private:
		entt::registry _registry; // entity used to determine which components belong together. registry contain the actual data.
		friend class Entity;
	};
};

#pragma once
#include <GameEngine/Scene/Scene.h>
#include <GameEngine/Entt/entt.h>

namespace RendererEngine{
	/*
	 * Entity
	 * @param id - the ID of the entity itself
	 * @note actual wrapper for entity for ECS
	 *
	 * */
	class Entity{
	public:
		Entity() = default;
		Entity(entt::entity handle, Scene* scene);
		Entity(const Entity&) = default;

		template<typename T, typename... Args>
		T& addComponent(Args&&... args){
			return _scene->_registry.emplace<T>(_entityHandler, std::forward<Args>(args)...);
		}

		template<typename T>
		T& getComponent() {
			// Checking if entity contains this component.
			if(!this->hasComponent<T>()){
				coreLogError("Entity does not have component!");
			}
			return _scene->_registry.get<T>(_entityHandler);
		}
		
		// Checking if entity has a component
		template<typename T>
		bool hasComponent(){
			// has<T> has been renamed to all_of<T>
			return _scene->_registry.all_of<T>(_entityHandler);
		}

		template<typename T>
		void removeComponent(){
			// Checking if the component exists
			if(!this->hasComponent<T>()){
				coreLogError("Entity does not have component!");
				return;
			}
			_scene->_registry.remove<T>(_entityHandler);
		}

	private:
		entt::entity _entityHandler{0};
		Scene* _scene = nullptr; // 12 bytes
	};
};

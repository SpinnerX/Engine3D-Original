#pragma once
#include <GameEngine/Scene/Entity.h>

namespace RendererEngine{
	/*
	 * class: ScriptableEntity
	 * @note All scripting should be part of ScriptableEntity
	 *
	 *
	 * */
	class ScriptableEntity{
	public:
		template<typename  T>
		T& getComponent(){
			if(!_entity.hasComponent<T>()){
				coreLogError("ScriptComponent Entity with this component could not be found");
			}

			return _entity.getComponent<T>();
		}



	private:
		Entity _entity;
		friend class Scene;
	};	
};

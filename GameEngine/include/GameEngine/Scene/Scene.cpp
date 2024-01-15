#include <GameEnginePrecompiledHeader.h>
#include <GameEngine/Scene/Scene.h>
#include <glm/glm.hpp>
#include <GameEngine/Scene/Components.h>

namespace RendererEngine{
	static void DoMath(const glm::mat4& transform){}

	static void onTransformConstruct(){}

	Scene::Scene(){
#if EXAMPLE_CODE
		entt::entity entity = _registry.create();

		_registry.emplace<TransformComponent>(entity, glm::mat4(1.0f));

		TransformComponent& component = _registry.get<TransformComponent>(entity);
		
		/* if(_registry.has<TransformComponent>(entity)){} */

		auto view = _registry.view<TransformComponent>();
		for(auto entity : view){
			TransformComponent& transform = view.get<TransformComponent>(entity);
		}

		auto group = _registry.group<TransformComponent>(entt::get<MeshComponent>);
		
		for(auto& entity : group){
			auto[transform, mesh] = group.get<TransformComponent, MeshComponent>(entity);
		}
		_registry.on_construct<TransformComponent>().connect<&onTransformConstruct>();
#endif

	}

	Scene::~Scene(){}
	
	entt::entity Scene::createEntity(){
		return _registry.create();
	}
	
	void Scene::onUpdate(Timestep ts){
		auto group = _registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);

		for(auto entity : group){
			auto[transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

			Renderer2D::drawQuad(transform, sprite._color);
		}
	}
};

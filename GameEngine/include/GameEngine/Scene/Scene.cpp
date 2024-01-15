#include <GameEnginePrecompiledHeader.h>
#include <GameEngine/Scene/Scene.h>
#include <glm/glm.hpp>
#include <GameEngine/Scene/Components.h>
#include <GameEngine/Scene/Entity.h>

namespace RendererEngine{
	Scene::Scene(){
/* #if EXAMPLE_CODE */
		/* entt::entity entity = _registry.create(); */

		/* _registry.emplace<TransformComponent>(entity, glm::mat4(1.0f)); */

		/* TransformComponent& component = _registry.get<TransformComponent>(entity); */
		
		/* /1* if(_registry.has<TransformComponent>(entity)){} *1/ */

		/* auto view = _registry.view<TransformComponent>(); */
		/* for(auto entity : view){ */
			/* TransformComponent& transform = view.get<TransformComponent>(entity); */
		/* } */

		/* auto group = _registry.group<TransformComponent>(entt::get<MeshComponent>); */
		
		/* for(auto& entity : group){ */
		/* 	auto[transform, mesh] = group.get<TransformComponent, MeshComponent>(entity); */
		/* } */
		/* _registry.on_construct<TransformComponent>().connect<&onTransformConstruct>(); */
/* #endif */

	}

	Scene::~Scene(){}
	
	Entity Scene::createEntity(const std::string& name){
		Entity entity = {_registry.create(), this};
		entity.addComponent<TransformComponent>();
		auto& tag = entity.addComponent<TagComponent>();
		tag.tag = name.empty() ? "Entity" : name;

		return entity;
	}
	
	void Scene::onUpdate(Timestep ts){
		auto group = _registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);

		for(auto entity : group){
			auto[transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

			Renderer2D::drawQuad(transform, sprite.color);
		}
	}
};

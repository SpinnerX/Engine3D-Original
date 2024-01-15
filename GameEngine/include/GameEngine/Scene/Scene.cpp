#include <GameEnginePrecompiledHeader.h>
#include <GameEngine/Scene/Scene.h>
#include <glm/glm.hpp>
#include <GameEngine/Scene/Components.h>
#include <GameEngine/Scene/Entity.h>

namespace RendererEngine{
	Scene::Scene(){
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
		// Rendering 2D
		Camera* mainCamera = nullptr;
		glm::mat4* cameraTransform = nullptr;

		{
		auto group = _registry.view<TransformComponent, CameraComponent>();

		for(auto entity : group){
			auto[transform, camera] = group.get<TransformComponent, CameraComponent>(entity);

			if(camera.isPrimary){
				mainCamera = &camera.camera;
				cameraTransform = &transform.transform;
				break;
			}
		}
		}
		
		// Checking mainCamera exists, then if the scene does not contain camera then do not render camera.
		if(mainCamera){
			Renderer2D::beginScene(mainCamera->getProjection(), *cameraTransform);
			auto group = _registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);

			for(auto entity : group){
				auto[transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

				Renderer2D::drawQuad(transform, sprite.color);
			}

			Renderer2D::endScene();
			
		}
		else coreLogError("Main Camera does not exist");


	}
};

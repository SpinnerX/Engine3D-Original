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
	
	void Scene::destroyEntity(Entity entity){
		_registry.destroy(entity);
	}

	void Scene::onUpdateRuntime(Timestep ts){
		{
			/*
			 *
			 * @note instead of doing [=] has been deprecated, so doing [=, this]
			 * @note [=, this] means that we are not making a copy of entity.
			 *
			 * @note TODO: Move to ScrenePlay::onScrenePlay
			 * */
			_registry.view<NativeScriptComponent>().each([=, this](auto entity, auto& nativeScriptComponent){
				// Checking for valid instance.
				// @note At beginning of each scene onUpdate()
				// @note Any entity that has NativeScriptComponent will have onCreate and onUpdate function called.
				if(!nativeScriptComponent.instance){
					nativeScriptComponent.instance = nativeScriptComponent.instantiateScript();
					nativeScriptComponent.instance->_entity = {entity, this};

					nativeScriptComponent.instance->onCreate();
				}

				nativeScriptComponent.instance->onUpdate(ts); // TODO: Should be called in onSceneStop.
			});
		}

		// Rendering 2D
		Camera* mainCamera = nullptr;
		glm::mat4 cameraTransform;

		{
		auto view = _registry.view<TransformComponent, CameraComponent>();

		for(auto entity : view){
			auto[transform, camera] = view.get<TransformComponent, CameraComponent>(entity);

			if(camera.isPrimary){
				mainCamera = &camera.camera;
				cameraTransform = transform.getTransform();
				break;
			}
		}
		}
		
		// Checking mainCamera exists, then if the scene does not contain camera then do not render camera.
		if(mainCamera){
			Renderer2D::beginScene(mainCamera->getProjection(), cameraTransform);
			auto group = _registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);

			for(auto entity : group){
				auto[transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

				Renderer2D::drawQuad(transform.getTransform(), sprite.color);
			}

			Renderer2D::endScene();
			
		}

	}
	
	void Scene::onUpdateEditor(Timestep ts, EditorCamera& camera){
		Renderer2D::beginScene(camera);
		auto group = _registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);

		for(auto entity : group){
			auto[transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

			Renderer2D::drawQuad(transform.getTransform(), sprite.color);
		}

		Renderer2D::endScene();
		
	}
	
	void Scene::onViewportResize(uint32_t width, uint32_t height){
		_viewportWidth = width;
		_viewportHeight = height;

		// Going through all entities that have the CameraComponent
		auto view = _registry.view<CameraComponent>();

		for(auto entity: view){
			auto& cameraComponent = view.get<CameraComponent>(entity);
			
			// @note resizing non fixed aspect ratio cameras.
			// @note Checking if the user through the editor wants to change the fixed aspect ratio (resizing)
			// @note probably the only time this wouldn't work is if adding a new camera component just after the scenes resize.
			// @note viewport able to now modify based on current added camera component.
			if(!cameraComponent.fixedAspectRatio){
				cameraComponent.camera.setViewportSize(_viewportWidth, _viewportHeight);
			}
			
		}
	}

	template<>
	void Scene::onComponentAdded<TransformComponent>(Entity entity, TransformComponent& component){}
	
	template<>
	void Scene::onComponentAdded<CameraComponent>(Entity entity, CameraComponent& component){
		component.camera.setViewportSize(_viewportWidth, _viewportHeight);
	}

	template<>
	void Scene::onComponentAdded<SpriteRendererComponent>(Entity entity, SpriteRendererComponent& component){
	}

	template<>
	void Scene::onComponentAdded<TagComponent>(Entity entity, TagComponent& component){

	}

	template<>
	void Scene::onComponentAdded<NativeScriptComponent>(Entity entity, NativeScriptComponent& component){

	}

	Entity Scene::getPrimaryCamera(){
		auto view = _registry.view<CameraComponent>();
		for(auto entity : view){
			const auto& camera = view.get<CameraComponent>(entity);

			if(camera.isPrimary){
				return Entity{entity, this};
			}
		}

		return {};
	}
};

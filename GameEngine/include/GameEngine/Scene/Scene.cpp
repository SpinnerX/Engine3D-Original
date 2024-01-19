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
		{
			_registry.view<NativeScriptComponent>().each([=](auto entity, auto& nativeScriptComponent){
				// Checking for valid instance.
				// @note At beginning of each scene onUpdate()
				// @note Any entity that has NativeScriptComponent will have onCreate and onUpdate function called.
				if(!nativeScriptComponent.instance){
					nativeScriptComponent.instantiateFun();
					nativeScriptComponent.onCreateFun(nativeScriptComponent.instance);
				}

				// Every frame
				nativeScriptComponent.onUpdateFun(nativeScriptComponent.instance, ts);
			});
		}

		// Rendering 2D
		Camera* mainCamera = nullptr;
		glm::mat4* cameraTransform = nullptr;

		{
		auto view = _registry.view<TransformComponent, CameraComponent>();

		for(auto entity : view){
			auto[transform, camera] = view.get<TransformComponent, CameraComponent>(entity);

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

	}
	
	void Scene::onViewportResize(uint32_t width, uint32_t height){
		_viewportWidth = width;
		_viewportHeight = height;

		// Going through all entities that have the CameraComponent
		auto view = _registry.view<CameraComponent>();

		for(auto entity: view){
			auto& cameraComponent = view.get<CameraComponent>(entity);
			
			// resizing non fixed aspect ratio cameras.
			// Checking if the user through the editor wants to change the fixed aspect ratio (resizing)
			// @note probably the only time this wouldn't work is if adding a new camera component just after the scenes resize.
			if(!cameraComponent.fixedAspectRatio){
				cameraComponent.camera.setViewportSize(_viewportWidth, _viewportHeight);
			}
		}
	}
};

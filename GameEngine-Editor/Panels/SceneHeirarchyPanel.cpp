#include "SceneHeirarchyPanel.h"
#include <GameEngine/Scene/Entity.h>
#include <GameEngine/Scene/Scene.h>
#include <GameEngine/Scene/Components.h>
#include <glm/gtc/type_ptr.hpp>

namespace RendererEngine{
	SceneHeirachyPanel::SceneHeirachyPanel(const Ref<Scene>& scene){
		setContext(scene);
	}

	void SceneHeirachyPanel::setContext(const Ref<Scene>& scene){
		_context = scene;
	}

	void SceneHeirachyPanel::onImguiRender(){
		// @note Drawing this whole scene heirarchy.
		// @note Setting up ImGui
		ImGui::Begin("Scene Heirarchy");
		_context->_registry.each([&](auto entityID){
			Entity entity = {entityID, _context.get() };
			
			// @note Wanting to check for a valid entity (may not want to list all entities)
			// @note Whenever creating an entity you give the tag component to it.
			drawEntityNode(entity);
		});
		
		// @note Deselecting entities/window tabs nodes
		// @note Left-click on a non entity panel will deselect the selected panels
		if(ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
			_selectionContext = {};

		ImGui::End();

		ImGui::Begin("Properties");
		
		// Checking if there is any selected context scene is valid
		if(_selectionContext){
			drawComponents(_selectionContext);
		}

		ImGui::End();
	}
	
	void SceneHeirachyPanel::drawEntityNode(Entity entity){
		auto& tc = entity.getComponent<TagComponent>().tag;

		// @param entity - actual entity that we want to pass in
		// @param flags - Click on actual arrow to expand and select that entity.
		// @param tc.c_str() - Actual name of the tree node.
		// @note entities are all unique and will not have the same entity in the same panel
		ImGuiTreeNodeFlags flags = ((_selectionContext == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
		
		bool opened = ImGui::TreeNodeEx((void *)(uint64_t)(uint32_t)entity, flags, tc.c_str());

		if(ImGui::IsItemClicked()){
			_selectionContext = entity;
		}
		
		// @note if child entities, recursively open those entities.
		if(opened){
			bool opened2 = ImGui::TreeNodeEx((void *)(uint64_t)((uint32_t)entity + 1000), flags, tc.c_str());
			if(opened2){
				ImGui::TreePop();
			}

			ImGui::TreePop();
		}

		/* ImGui::Text("%s", tc.tag.c_str()); */
	}
	
	void SceneHeirachyPanel::drawComponents(Entity entity){
		// checking if entity has components.
		if(entity.hasComponent<TagComponent>()){
			auto& tag = entity.getComponent<TagComponent>().tag;

			// @context Camera0
			char buffer[256];
			
			// To make null terminated.
			memset(buffer, 0, sizeof(buffer));
			strcpy(buffer, tag.c_str());

			if(ImGui::InputText("Tag", buffer, sizeof(buffer))) {
				tag = std::string(buffer);
			}
		}


		
		// @params translation, rotation, scale.
		// @note handling those controls the transformation of entities.
		// @note TODO probably change the api call to the following below for entity and components retrieval.
		/*
		 drawComponent<CameraComponent>("Camera"), [](){
			auto& src = entity.getComponent<SpriteRendererComponent>();
			ImGui::ColorEdit4("Color", glm::value_ptr(src.color));
		 });

		 * */
		if(entity.hasComponent<TransformComponent>()){
			
			// Creating our headers.
			if(ImGui::TreeNodeEx((void *)typeid(TransformComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Transform")){
				auto& transform = entity.getComponent<TransformComponent>().transform;
				ImGui::DragFloat3("Position", glm::value_ptr(transform[3]), 0.5f);

				ImGui::TreePop();
			}
		}

		if(entity.hasComponent<CameraComponent>()){
			if(ImGui::TreeNodeEx((void *)typeid(CameraComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Camera")){
				auto& cameraComponent = entity.getComponent<CameraComponent>();
				auto& camera = cameraComponent.camera;
				
				ImGui::Checkbox("Primary", &cameraComponent.isPrimary);


				const char* projectionTypeStrings[] = {"Perspective", "Orthographic"};
				const char* currentProjectionTypeString = projectionTypeStrings[(int)cameraComponent.camera.getProjectionType()];

				// @note if BeginCombo has started.
				if(ImGui::BeginCombo("Projection", currentProjectionTypeString)){
					
					// @note seeing what currently selected projection type is. 
					for(int i = 0; i < 2; i++){

						// @note handling if the projection type selected is valid and selected
						bool isSelected = (currentProjectionTypeString == projectionTypeStrings[i]);
						if(ImGui::Selectable(projectionTypeStrings[i], isSelected)){
							currentProjectionTypeString = projectionTypeStrings[i];
							camera.setProjectionType((SceneCamera::ProjectionType)i);
						}
						
						// @note checking if already selected then setting the default focus.
						if(isSelected){
							ImGui::SetItemDefaultFocus();
						}
					}

					ImGui::EndCombo();
				}
				
				// @note checking if the camera component is orthographic.
				if(cameraComponent.camera.getProjectionType() == SceneCamera::ProjectionType::Perspective){
					float verticalFov = glm::degrees(camera.getPerspectiveVerticalFOV());

					if(ImGui::DragFloat("FOV", &verticalFov))
						camera.setPerspectiveVerticalFOV(glm::radians(verticalFov));

					float perspNearClip = camera.getPerspectiveNearClip();
					if(ImGui::DragFloat("Near", &perspNearClip))
						camera.setPerspectiveNearClip(perspNearClip);
					
					float perspFarClip = camera.getPerspectiveFarClip();
					if(ImGui::DragFloat("Far", &perspFarClip))
						camera.setPerspectiveFarClip(perspFarClip);
				}
				
				if(cameraComponent.camera.getProjectionType() == SceneCamera::ProjectionType::Orthographic){
					float orthoSize = camera.getOrthographicSize();

					if(ImGui::DragFloat("Size", &orthoSize))
						camera.setOrthographicSize(orthoSize);

					float nearClip = camera.getOrthoNearClip();
					if(ImGui::DragFloat("Near", &nearClip))
						camera.setOrthoNearClip(nearClip);
					
					float farClip = camera.getOrthoFarClip();
					if(ImGui::DragFloat("Far", &farClip))
						camera.setOrthoNearClip(farClip);
					ImGui::Checkbox("Fixed Aspect Ratio", &cameraComponent.fixedAspectRatio);
				}

				ImGui::TreePop();
			}
		}

		if(entity.hasComponent<SpriteRendererComponent>()){
			if(ImGui::TreeNodeEx((void *)typeid(SpriteRendererComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Sprite Renderer")){
				auto& spriteRenderComponent = entity.getComponent<SpriteRendererComponent>();
				ImGui::ColorEdit4("Color", glm::value_ptr(spriteRenderComponent.color));
				ImGui::TreePop();
			}
		}
	}
};

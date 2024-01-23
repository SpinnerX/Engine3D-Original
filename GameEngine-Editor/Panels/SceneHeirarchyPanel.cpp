#include "SceneHeirarchyPanel.h"
#include <GameEngine/Scene/Entity.h>
#include <GameEngine/Scene/Scene.h>
#include <GameEngine/Scene/Components.h>

namespace RendererEngine{
	SceneHeirachyPanel::SceneHeirachyPanel(const Ref<Scene>& scene){
		setContext(scene);
	}

	void SceneHeirachyPanel::setContext(const Ref<Scene>& scene){
		_context = scene;
	}

	void SceneHeirachyPanel::onImguiRender(){
		// Drawing this whole scene heirarchy.
		// Setting up ImGui
		ImGui::Begin("Scene Heirarchy");
		_context->_registry.each([&](auto entityID){
			Entity entity = {entityID, _context.get() };
			
			// @note Wanting to check for a valid entity (may not want to list all entities)
			// @note Whenever creating an entity you give the tag component to it.
			drawEntityNode(entity);
		});
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
};

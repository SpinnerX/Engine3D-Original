#pragma once
#include <GameEngine/Core/core.h>
#include <imgui/imgui.h>
#include <GameEngine/Scene/Scene.h>
#include <GameEngine/Scene/Entity.h>

namespace RendererEngine{
	/*
	 *
	 * @function setContext
	 * @note setting the scene context.
	 * @note setting up scene heirarchy panel.
	 *
	 * */
	class SceneHeirachyPanel{
	public:
		SceneHeirachyPanel() = default;
		SceneHeirachyPanel(const Ref<Scene>& scene);

		void setContext(const Ref<Scene>& scene);

		void onImguiRender();

	private:
		void drawEntityNode(Entity entity);

	private:
		Ref<Scene> _context;
		Entity _selectionContext;
	};
};

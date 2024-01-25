#pragma once
#include <GameEngine/Core/GameEngine.h>
#include "Panels/SceneHeirarchyPanel.h"

namespace RendererEngine{
	class EditorLayer : public Layer{
	public:
EditorLayer();
	
		virtual ~EditorLayer() = default;

		virtual void onAttach() override;
		virtual void onDetach() override;

		virtual void onUpdate(Timestep ts) override;

		virtual void onImguiRender() override;

		virtual void onEvent(Event& e) override;
	
	private:
		bool onKeyPressed(KeyPressedEvent& e);

		void newScene();
		void openScene();
		void saveAs();

	private:
		OrthographicCameraController _cameraController;

		// This'll be temporary only!
		Ref<VertexArray> _squareVertexArrays;
		Ref<Shader> _flatColorShader;
		
		bool _isViewportFocused = false;
		bool _isViewportHovered = false;

		Ref<Texture2D> _checkerboardTexture;
		Ref<FrameBuffer> _framebuffers;

		SceneHeirachyPanel _sceneHeirarchyPanel;

		Ref<Scene> _activeScene;
		Entity _squareEntity;
		Entity _squareEntity2;
		Entity _cameraEntity;
		Entity _cameraSecond;
		bool isPrimaryCamera = true;
		
		int _gizmoType = -1; // @note this is going to be the type of operationt he gizmal is going to be.

		glm::vec2 _viewportSize = {0, 0};
		glm::vec4 _squareColor;
	};
};

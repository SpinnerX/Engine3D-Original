#include <GameEnginePrecompiledHeader.h>
#include "EditorLayer.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GameEngine/platforms/OpenGL/OpenGLShader.h>
#include <GameEngine/Entt/entt.h>
#include <GameEngine/Scene/SceneSerializer.h>
#include <GameEngine/Utils/PlatformUtils.h>
#include <ImGuizmo/ImGuizmo.h>
#include <GameEngine/Math/Math.h>

namespace RendererEngine{
	EditorLayer::EditorLayer() : Layer("Sandbox2D"){
	}

	void EditorLayer::onAttach(){
		RENDER_PROFILE_FUNCTION();
		_checkerboardTexture = Texture2D::Create("assets/Checkerboard.png");
		/* _cameraController.setZoomLevel(3.0f); */

		FrameBufferSpecifications frameBufSpecs;
		frameBufSpecs.width = 1280;
		frameBufSpecs.height = 720;

	
		_framebuffers = FrameBuffer::Create(frameBufSpecs); // Creating out frame buffer
		_activeScene = CreateRef<Scene>();

		_editorCamera = EditorCamera(100.0f, 1.778f, 0.1f, 1000.0f);
		
		_sceneHeirarchyPanel.setContext(_activeScene);
	}

	void EditorLayer::onDetach(){
		RENDER_PROFILE_FUNCTION();
	}

	void EditorLayer::onUpdate(Timestep ts){
		RENDER_PROFILE_FUNCTION();
		
		// Updating scripts
		// Iterate all entities in ScriptableEntity
		
		if(FrameBufferSpecifications spec = _framebuffers->getSpecifications();
				_viewportSize.x > 0.0f and _viewportSize.y > 0.0f &&
				(spec.width != _viewportSize.x || spec.height != _viewportSize.y)){
			_framebuffers->resize((uint32_t)_viewportSize.x, (uint32_t)_viewportSize.y);
			_editorCamera.setViewportSize(_viewportSize.x, _viewportSize.y);
			_activeScene->onViewportResize(_viewportSize.x, _viewportSize.y); // viewport resizing every time the window size is changed
		}
		
		// Update (if mouse cursor is focused in window.)
		if(_isViewportFocused){
			/* _cameraController.onUpdate(ts); */
			_editorCamera.onUpdate(ts);
		}


		
		// Render
		Renderer2D::resetStats();
		_framebuffers->bind();
		RendererCommand::setClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		RendererCommand::clear();

		_activeScene->onUpdateEditor(ts, _editorCamera);

		_framebuffers->unbind();
	}

	void EditorLayer::onImguiRender(){
		static bool dockSpaceOpened = true;
		static bool opt_fullscreen = true;
		static bool opt_padding = false;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen){
			const ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->Pos);
			ImGui::SetNextWindowSize(viewport->Size);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}
		else{
			dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
		}

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
		// and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;
		
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &dockSpaceOpened, window_flags);
		ImGui::PopStyleVar();

		if(opt_fullscreen)
			ImGui::PopStyleVar(2);

		// Submit the DockSpace
		ImGuiIO& io = ImGui::GetIO();
		float minWinSizeX = 370.0f;
		ImGuiStyle& style = ImGui::GetStyle();
		style.WindowMinSize.x = 370.0f;
		

		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable){
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}
		style.WindowMinSize.x = minWinSizeX;
	
		if (ImGui::BeginMenuBar()){
			if (ImGui::BeginMenu("File")){
				
				if(ImGui::MenuItem("New", "Ctrl+N")){
					newScene();
				}

				ImGui::Separator();

				if(ImGui::MenuItem("Open", "Ctrl+O")){
					openScene();
				}
				
				ImGui::Separator();

				if(ImGui::MenuItem("Save as", "Ctrl+Shift+s")){
					saveAs();
				}
				
				ImGui::Separator();


				if(ImGui::MenuItem("Exit")) Application::Get().close();

				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}
		
		_sceneHeirarchyPanel.onImguiRender();

		ImGui::Begin("Stats");

		auto stats = Renderer2D::getStats();
		ImGui::Text("Renderer2D Stats");
		ImGui::Text("Draw Calls %d", stats.drawCalls);
		ImGui::Text("Quads: %d", stats.quadCount);
		ImGui::Text("Vertices: %d", stats.getTotalVertexCount());
		ImGui::Text("Indices: %d", stats.getTotalIndexCount());

		ImGui::End();
	
		// Starting the viewports
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{0, 0});
		ImGui::Begin("Viewport");
		
		// Checking if window is focused, then to not block incoming events
		_isViewportFocused = ImGui::IsWindowFocused(); // If viewport is focused then we don't want to block incoming events.
		_isViewportHovered = ImGui::IsWindowHovered();

		Application::Get().getImGuiLayer()->setBlockEvents(!_isViewportFocused && !_isViewportHovered); // if either out of focused or hovered

		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		_viewportSize = {_viewportSize.x, _viewportSize.y};
		// Assuming the viewPortPanelSize is this type.
		if(_viewportSize != *((glm::vec2 *)&viewportPanelSize) && viewportPanelSize.x > 0 && viewportPanelSize.y > 0){
			// Recreating the frame buffer.
			_framebuffers->resize((uint32_t)viewportPanelSize.x, (uint32_t)viewportPanelSize.y);
			_viewportSize = {viewportPanelSize.x, viewportPanelSize.y};
			/* _cameraController.onResize(_viewportSize.x, _viewportSize.y); */
		}

		// By passing this renderer ID, this gives us the ID of the texture that we want to render.
		uint32_t textureID = _framebuffers->getColorAttachmentRendererID(); // Getting color buffer from frame buffer
		ImGui::Image(reinterpret_cast<void *>(textureID), ImVec2{_viewportSize.x, _viewportSize.y}, ImVec2{0, 1}, ImVec2{1, 0});

		
		// Gizmos
		Entity selectedEntity = _sceneHeirarchyPanel.getSelectedEntity();
		
		// @note only wanting to select the gizmo only when selected an entity and the type isn't -1 (unknown)
		if(selectedEntity && _gizmoType != -1){
			ImGuizmo::SetOrthographic(false);
			ImGuizmo::SetDrawlist();
			
			float windowWidth = (float)ImGui::GetWindowWidth();
			float windowHeight = (float)ImGui::GetWindowHeight();

			ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, windowWidth, windowHeight); // Setting the rectangle.

			// Drawing the gismo (and figuring out where the camera is.
			// @note Getting the camera information
			// Camera Runtime 
			/* auto cameraEntity = _activeScene->getPrimaryCamera(); */
			/* const auto& camera = cameraEntity.getComponent<CameraComponent>().camera; */
			/* const glm::mat4& cameraProjection = camera.getProjection(); */
			/* glm::mat4 cameraView = glm::inverse(cameraEntity.getComponent<TransformComponent>().getTransform()); *1/ */
			


			/* glm::mat4 deleteMeTemp_cameraView = glm::inverse(cameraEntity.getComponent<TransformComponent>().getTransform()); */
			
			// Editor Camera
			const glm::mat4& cameraProjection = _editorCamera.getProjection();
			glm::mat4 cameraView = _editorCamera.getViewMatrix();

			// Snapping
			bool isSnap = InputPoll::isKeyPressed(KeyCode::LeftControl);
			float snapValue = 0.5f;

			if(_gizmoType == ImGuizmo::OPERATION::ROTATE)
				snapValue = 45.0f;

			float snapValues[3] = {snapValue, snapValue, snapValue};
			
			// Enttiy Transform
			auto& tc = selectedEntity.getComponent<TransformComponent>();
			glm::mat4 transform = tc.getTransform();


			ImGuizmo::Manipulate(glm::value_ptr(cameraView), glm::value_ptr(cameraProjection), (ImGuizmo::OPERATION)_gizmoType, ImGuizmo::LOCAL, glm::value_ptr(transform), nullptr, isSnap ? snapValues : nullptr);
			
			// @note checking if gizmo is selected.
			if(ImGuizmo::IsUsing()){
				glm::vec3 translation, rotation, scale;
				Math::decomposeTransform(transform, translation, rotation, scale);	
				glm::vec3 deltaRotation = rotation - tc.rotation;
				tc.translation = translation;
				tc.rotation += deltaRotation; // @note preventing gimbal lock
				tc.scale = scale;
			}
		}




		ImGui::End();
		ImGui::PopStyleVar();



		ImGui::End();

	}

	void EditorLayer::onEvent(Event& e){
		/* _cameraController.onEvent(e); */
		_editorCamera.onEvent(e);

		// Enabling key bindings
		EventDispatcher dispatcher(e);

		dispatcher.Dispatch<KeyPressedEvent>(bind_function(this, &EditorLayer::onKeyPressed));
	}
	
	bool EditorLayer::onKeyPressed(KeyPressedEvent& e){
		// Only works with shortcuts
		if(e.GetRepeatCount() > 0)
			return false;
		bool control = InputPoll::isKeyPressed(KeyCode::LeftControl) || InputPoll::isKeyPressed(KeyCode::RightControl);
		bool shift = InputPoll::isKeyPressed(KeyCode::LeftShift) || InputPoll::isKeyPressed(KeyCode::RightShift);

		switch (e.GetKeyCode()) {
		case KeyCode::N:
		{
			  if(control){
				newScene();
			  }
		}
			  break;

		case KeyCode::O:
		{
			  if(control){
					openScene();
			  }
		}
			  break;

		case KeyCode::S:
		{
			if(control && shift){
				saveAs();
			}
		}
			break;
			// Gizmos controls
		case KeyCode::Q: // Selection
			_gizmoType = -1;
			break;
		case  KeyCode::W:
			_gizmoType = ImGuizmo::OPERATION::TRANSLATE;
			break;
		case KeyCode::E:
			_gizmoType = ImGuizmo::OPERATION::ROTATE;
			break;
		case KeyCode::R:
			_gizmoType = ImGuizmo::OPERATION::SCALE;
			break;
		default:
			break;
		}

		return false;
	}
	void EditorLayer::newScene(){
		_activeScene = CreateRef<Scene>();
		_activeScene->onViewportResize((uint32_t)_viewportSize.x, (uint32_t)_viewportSize.y);
		_sceneHeirarchyPanel.setContext(_activeScene);
	}

	void EditorLayer::openScene(){
		
		std::string filepath = FileDialogs::openFile("Game Engine (*.engine)\0*.engine\0");
		coreLogTrace("Trace #2 -- filepath = {0}\n", filepath);

		_activeScene = CreateRef<Scene>();
		_activeScene->onViewportResize((uint32_t)_viewportSize.x, (uint32_t)_viewportSize.y);
		_sceneHeirarchyPanel.setContext(_activeScene);

		SceneSerializer serializer(_activeScene);
		serializer.deserialize(filepath);
	}

	void EditorLayer::saveAs(){
		std::string filepath = FileDialogs::saveFile("Game Engine (*.engine)\0*.engine\0");
		SceneSerializer serializer(_activeScene);
		serializer.serializer(filepath);
	}
};

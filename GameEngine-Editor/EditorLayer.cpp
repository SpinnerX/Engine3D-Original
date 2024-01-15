#include "EditorLayer.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GameEngine/platforms/OpenGL/OpenGLShader.h>
#include <GameEngine/Entt/entt.h>

namespace RendererEngine{
	EditorLayer::EditorLayer() : Layer("Sandbox2D"), _cameraController(1280.0f / 720.0f){
	}

	void EditorLayer::onAttach(){
		RENDER_PROFILE_FUNCTION();
		_checkerboardTexture = Texture2D::Create("assets/Checkerboard.png");
		_cameraController.setZoomLevel(3.0f);

		FrameBufferSpecifications frameBufSpecs;
		frameBufSpecs.width = 1280;
		frameBufSpecs.height = 720;

	
		_framebuffers = FrameBuffer::Create(frameBufSpecs); // Creating out frame buffer
		_activeScene = CreateRef<Scene>();
		


		// Creating an entity in the scene.
		auto square = _activeScene->createEntity("Green Square");
		square.addComponent<SpriteRendererComponent>(glm::vec4{0.0f, 1.0f, 0.0f, 1.0f});
		_squareEntity = square;


	}

	void EditorLayer::onDetach(){
		RENDER_PROFILE_FUNCTION();
	}

	void EditorLayer::onUpdate(Timestep ts){
		RENDER_PROFILE_FUNCTION();
	
		// Update (if mouse cursor is focused in window.)
		if(_isViewportFocused)
			_cameraController.onUpdate(ts);
		
		// Render	
		Renderer2D::resetStats();
		_framebuffers->bind();
		RendererCommand::setClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		RendererCommand::clear();


	
		Renderer2D::beginScene(_cameraController.getCamera());
		// Updating scene
		_activeScene->onUpdate(ts);
		
		Renderer2D::endScene();

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
			ImGui::SetNextWindowPos(viewport->WorkPos);
			ImGui::SetNextWindowSize(viewport->WorkSize);
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

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
		if (!opt_padding)
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

		ImGui::Begin("DockSpace Demo", &dockSpaceOpened, window_flags);
		if (!opt_padding)
			ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// Submit the DockSpace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable){
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}
	
		/*
		*
		* ImGui::BeginMenuBar()
		* @note this is how you can add items to the menu bar at the top of the window.
		*
		*
		* */
		if (ImGui::BeginMenuBar()){
			if (ImGui::BeginMenu("File")){

				if(ImGui::MenuItem("Exit")) Application::Get().close();

				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		ImGui::End();


		ImGui::Begin("Settings");

		auto stats = Renderer2D::getStats();
		ImGui::Text("Renderer2D Stats");
		ImGui::Text("Draw Calls %d", stats.drawCalls);
		ImGui::Text("Quads: %d", stats.quadCount);
		ImGui::Text("Vertices: %d", stats.getTotalVertexCount());
		ImGui::Text("Indices: %d", stats.getTotalIndexCount());


		
		ImGui::Separator();
		auto& tag = _squareEntity.getComponent<TagComponent>().tag;
		ImGui::Text("%s", tag.c_str());

		auto& squareColor = _squareEntity.getComponent<SpriteRendererComponent>().color;
		ImGui::ColorEdit4("Square Color", glm::value_ptr(squareColor));
		
		ImGui::Separator();





	
		// Starting the viewports
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{0, 0});
		ImGui::Begin("Viewport");
		
		// Checking if window is focused, then to not block incoming events
		_isViewportFocused = ImGui::IsWindowFocused(); // If viewport is focused then we don't want to block incoming events.
		_isViewportHovered = ImGui::IsWindowHovered();

		Application::Get().getImGuiLayer()->setBlockEvents(!_isViewportFocused || !_isViewportHovered); // if either out of focused or hovered

		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();

		// Assuming the viewPortPanelSize is this type.
		if(_viewportSize != *((glm::vec2 *)&viewportPanelSize) && viewportPanelSize.x > 0 && viewportPanelSize.y > 0){
			// Recreating the frame buffer.
			_framebuffers->resize((uint32_t)viewportPanelSize.x, (uint32_t)viewportPanelSize.y);
			_viewportSize = {viewportPanelSize.x, viewportPanelSize.y};

			_cameraController.onResize(_viewportSize.x, _viewportSize.y);
		}

		// By passing this renderer ID, this gives us the ID of the texture that we want to render.
		uint32_t textureID = _framebuffers->getColorAttachmentRendererID(); // Getting color buffer from frame buffer
		ImGui::Image(reinterpret_cast<void *>(textureID), ImVec2{_viewportSize.x, _viewportSize.y}, ImVec2{0, 1}, ImVec2{1, 0});
		ImGui::End();
		ImGui::PopStyleVar();



		ImGui::End();

	}

	void EditorLayer::onEvent(Event& e){
		_cameraController.onEvent(e);
	}
};

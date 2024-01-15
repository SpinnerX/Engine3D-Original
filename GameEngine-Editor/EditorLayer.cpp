#include "EditorLayer.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GameEngine/platforms/OpenGL/OpenGLShader.h>

namespace RendererEngine{
	EditorLayer::EditorLayer() : Layer("Sandbox2D"), _cameraController(1280.0f / 720.0f){
	}

	void EditorLayer::onAttach(){
		RENDER_PROFILE_FUNCTION();
		_checkerboardTexture = RendererEngine::Texture2D::Create("assets/Checkerboard.png");
		_cameraController.setZoomLevel(3.0f);

		RendererEngine::FrameBufferSpecifications frameBufSpecs;
		frameBufSpecs.width = 1280;
		frameBufSpecs.height = 720;

	
		_framebuffers = RendererEngine::FrameBuffer::Create(frameBufSpecs); // Creating out frame buffer
	}

	void EditorLayer::onDetach(){
		RENDER_PROFILE_FUNCTION();
	}

	void EditorLayer::onUpdate(RendererEngine::Timestep ts){
		RENDER_PROFILE_FUNCTION();
	
		// Update
		_cameraController.onUpdate(ts);
	
		RendererEngine::Renderer2D::resetStats();

		// Render
		{
			RENDER_PROFILE_FUNCTION();
			_framebuffers->bind();
			RendererEngine::RendererCommand::setClearColor({ 0.1f, 0.1f, 0.1f, 1 });
			RendererEngine::RendererCommand::clear();
		}
	
		{
			RENDER_PROFILE_FUNCTION();
			RendererEngine::Renderer2D::beginScene(_cameraController.getCamera());
			static float rotation = 0.0f;
			rotation += ts * 50.0f;


			// Our draw quads, for drawing our rectangles.
			RendererEngine::Renderer2D::drawRotatedQuad({1.0f, 0.0f}, {0.8f, 0.8f}, glm::radians(-45.0f), {0.8f, 0.2f, 0.3f, 1.0f}); // Red shape
			RendererEngine::Renderer2D::drawQuad({-1.0f, 0.0f}, {0.8f, 0.8f}, {0.8f, 0.2f, 0.3f, 1.0f}); // Red shape
			RendererEngine::Renderer2D::drawQuad({0.5f, -0.5f}, {0.5f, 0.75f}, {0.2f, 0.3f, 0.8f, 1.0f}); // blue shape
			RendererEngine::Renderer2D::drawQuad({0.0f, 0.0f, -0.1f}, {20.0f, 20.0f}, _checkerboardTexture, 10.0f); // checkerboard texture shape
			RendererEngine::Renderer2D::drawRotatedQuad({ -2.0f, 0.0f, 0.0f}, {1.0f, 1.0f}, glm::radians(rotation), _checkerboardTexture, 20.0f); // checkerboard texture shape
	
			RendererEngine::Renderer2D::endScene();

			RendererEngine::Renderer2D::beginScene(_cameraController.getCamera());

			for(float y = -5.0f; y < 5.0f; y += 0.5f){
				for(float x = -5.0f; x < 5.0f; x += 0.5f){
					glm::vec4 color = { (x + 0.5f) / 10.f, 0.4f, (y + 5.0f) / 10.0f, 0.7f};
					RendererEngine::Renderer2D::drawQuad({x, y}, {0.45f, 0.45f}, color);
				}
			
			}

			RendererEngine::Renderer2D::endScene();
			_framebuffers->unbind();
		}
	}

	void EditorLayer::onImguiRender(){
		// Quick Note: Switch to true to enable docking.
		static bool dockingEnabled = true;
	
		if(dockingEnabled){
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

					if(ImGui::MenuItem("Exit")) RendererEngine::Application::Get().close();

					ImGui::EndMenu();
				}
				ImGui::EndMenuBar();
			}

			ImGui::End();
		}


		ImGui::Begin("Settings");

		auto stats = RendererEngine::Renderer2D::getStats();
		ImGui::Text("Renderer2D Stats");
		ImGui::Text("Draw Calls %d", stats.drawCalls);
		ImGui::Text("Quads: %d", stats.quadCount);
		ImGui::Text("Vertices: %d", stats.getTotalVertexCount());
		ImGui::Text("Indices: %d", stats.getTotalIndexCount());

		ImGui::ColorEdit4("Square Color", glm::value_ptr(_squareColor));
	
		// By passing this renderer ID, this gives us the ID of the texture that we want to render.
		/* uint32_t textureID = _checkerboardTexture->getRendererID(); */
		uint32_t textureID = _framebuffers->getColorAttachmentRendererID(); // Getting color buffer from frame buffer
		/* ImGui::Image(reinterpret_cast<void *>(textureID), ImVec2{1280.0f, 720.0f}, ImVec2{0, 1}, ImVec2{1, 0}); */
		ImGui::Image(reinterpret_cast<void *>(textureID), ImVec2{1280.0f, 720.0f}, ImVec2{0, 1}, ImVec2{1, 0});
		ImGui::End();

	}

	void EditorLayer::onEvent(RendererEngine::Event& e){
		_cameraController.onEvent(e);
	}
};

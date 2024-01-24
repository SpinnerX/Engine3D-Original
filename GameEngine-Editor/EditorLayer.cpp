#include <GameEnginePrecompiledHeader.h>
#include "EditorLayer.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GameEngine/platforms/OpenGL/OpenGLShader.h>
#include <GameEngine/Entt/entt.h>
#include <GameEngine/Scene/SceneSerializer.h>

namespace RendererEngine{
	EditorLayer::EditorLayer() : Layer("Sandbox2D"), _cameraController(1280.0f / 720.0f), _squareColor({ 0.2f, 0.3f, 0.8f, 1.0f }){
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
		

#if 0
		// Creating an entity in the scene.
		auto square = _activeScene->createEntity("Green Square");
		square.addComponent<SpriteRendererComponent>(glm::vec4{0.0f, 1.0f, 0.0f, 1.0f});

		auto redSquare = _activeScene->createEntity("Red Square");
		redSquare.addComponent<SpriteRendererComponent>(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
		
		_squareEntity = square;

		// Creating our camera component.
		_cameraEntity = _activeScene->createEntity("Camera A");
		_cameraEntity.addComponent<CameraComponent>();
		
		_cameraSecond = _activeScene->createEntity("Camera B");
		auto& cc = _cameraSecond.addComponent<CameraComponent>();
		cc.isPrimary = false;

		// Standard script 
		class CameraController : public ScriptableEntity{
		public:

			// Function gets called when entity gets created.
			// We need onCreate instance.
			void onCreate(){
				/* getComponent<TransformComponent>(); */
				/* coreLogInfo("CameraComponentController::onCreate() called!\n"); */
				auto& translation = getComponent<TransformComponent>().translation;
				translation.x = rand() % 10 - 5.0f;
				/* transform.transform[3][0] = rand() % 10 - 5.0f; */
			}
			
			// Where the scenes get updated
			void onUpdate(Timestep ts){
				/* coreLogInfo("CameraComponentController::onUpdate() TimeStep = {} has been called!\n", fmt::streamed(ts)); */
				auto& translation = getComponent<TransformComponent>().translation;
				float speed = 5.f;
				if(InputPoll::isKeyPressed(KeyCode::A)){
					/* transform.transform[3][0] -= speed * ts; */
					translation.x -= speed * ts;
				}
				else if(InputPoll::isKeyPressed(KeyCode::D)){
					/* transform.transform[3][0] += speed * ts; */
					translation.x += speed * ts;
				}
				else if(InputPoll::isKeyPressed(KeyCode::W)){
					/* transform.transform[3][1] += speed * ts; */
					translation.y += speed * ts;
				}
				else if(InputPoll::isKeyPressed(KeyCode::S)){
					/* transform.transform[3][1] -= speed * ts; */
					translation.y -= speed * ts;
				}
				
			}
			
			// To destroy entities, collision callbacks, etc.
			void onDestroy(){
				/* coreLogInfo("CameraComponentController::onDestroy() called!\n"); */
			}
		};
		
		// Idea in API usage.
		_cameraSecond.addComponent<NativeScriptComponent>().bind<CameraController>();
		_cameraEntity.addComponent<NativeScriptComponent>().bind<CameraController>();

#endif
		_sceneHeirarchyPanel.setContext(_activeScene);

		/* serializer.serializer("assets/scene/Example.engine"); */
	}

	void EditorLayer::onDetach(){
		RENDER_PROFILE_FUNCTION();
	}

	void EditorLayer::onUpdate(Timestep ts){
		RENDER_PROFILE_FUNCTION();
		
		// Updating scripts
		// Iterate all entities in ScriptableEntity


		_activeScene->onViewportResize(_viewportSize.x, _viewportSize.y); // viewport resizing every time the window size is changed
		
		
		// Update (if mouse cursor is focused in window.)
		if(_isViewportFocused)
			_cameraController.onUpdate(ts);
		
		// Render
		Renderer2D::resetStats();
		_framebuffers->bind();
		RendererCommand::setClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		RendererCommand::clear();

		_activeScene->onUpdate(ts);

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
				
				if(ImGui::MenuItem("Serialize")){
					SceneSerializer serializer(_activeScene);
					serializer.serializer("assets/scene/Example.engine");
				}

				if(ImGui::MenuItem("Deserialize")){
					SceneSerializer serializer(_activeScene);
					serializer.deserialize("assets/scene/Example.engine");
				}

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

		Application::Get().getImGuiLayer()->setBlockEvents(!_isViewportFocused || !_isViewportHovered); // if either out of focused or hovered

		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		_viewportSize = {_viewportSize.x, _viewportSize.y};
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

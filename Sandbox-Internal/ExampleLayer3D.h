#pragma once
#include <Engine3D/Engine3DPrecompiledHeader.h>
#include <Engine3D/Event/KeyCodes.h>
#include <Engine3D/Renderer2D/OrthographicCameraController.h>

namespace Engine3D{
	class ExampleLayer3D : public Layer{
	public:
		ExampleLayer3D() : Layer("Test Layer"), controller(1280.0f/720.0f){
		}

		void OnAttach() override {
			checkboardTexture = Texture2D::Create("assets/Checkerboard.png");
			controller.setZoomLevel(5.0f); // @note Higher the offset, the wider we zoom outwards.
		}

		void OnDetach() override {}

		void OnUpdate(Timestep ts) override {
			controller.OnUpdate(ts);
	
			static float  rotation = 0.0f;
			rotation += ts * 50.0f;

			Renderer::Begin(controller.getCamera());
			// Renderer2D::DrawQuad({0.f, 0.f}, {10.f, 10.f}, {0.f, 0.f, 1.f, 1.f});
			// Renderer2D::DrawQuad({0.0f, 0.0f}, {5.f, 5.f}, {0.8, 0.2f, 0.3f, 1.0f});
			Renderer2D::DrawRotatedQuad({ -2.0f, 0.0f, 0.0f}, {1.0f, 1.0f}, glm::radians(rotation), checkboardTexture, 20.0f); //@note Checkerboard texture shape (and making this texture specifically rotate)

			// @note This will draw tiles squares as color gradients
			for(float y = -5.0f; y < 5.0f; y += 0.5f){
				for(float x = -5.0f; x < 5.0f; x += 0.5f){
					glm::vec4 color = { (x + 0.5f) / 10.f, 0.4f, (y + 5.0f) / 10.0f, 0.7f};
					Renderer2D::DrawQuad({x, y}, {0.45f, 0.45f}, color);
				}
			}
			Renderer::End();
		}

		void OnEvent(Event& e) override {
			controller.onEvent(e);

			if(InputPoll::IsKeyPressed(ENGINE_KEY_ESCAPE)){
				Application::Close();
			}
		}


		void OnUIRender() override {
		}

	private:
		Ref<Scene> activeScene;
		OrthographicCameraController controller;
		Ref<VertexArray> vertexArr;
		Ref<Shader> shader;

		Ref<Texture2D> checkboardTexture;
		glm::vec4 squareColor = {0.2f, 0.3f, 0.8f, 1.0f};
	};
};

#pragma once
#include <GameEngine/Renderer/OrthographicCamera.h>
#include <GameEngine/Core/Timestep.h>
#include <GameEngine/Events/ApplicationEvent.h>
#include <GameEngine/Events/Event.h>
#include <GameEngine/Events/MouseEvent.h>


namespace RendererEngine{

	class OrthographicCameraController{
	public:	
		OrthographicCameraController(float aspectRatio, bool rotation=false); // vertically when camera starts up that there is 2 units of space (then to get correct aspect ratio, have: aspectratio * 2 units)
		
		void getProjection();
		
		void onUpdate(Timestep ts);
		void onEvent(Event& e);

		OrthographicCamera& getCamera() { return _camera; }
		OrthographicCamera getCamera() const { return _camera; }

	private:
		bool onMouseScrolled(MouseScrolledEvent& e);
		bool onWindowResized(WindowResizeEvent& e);

	private:
		float _aspectRatio;
		float _zoomLevel = 1.f; // Higher zoom level is, the further out you zoomed inwards.
		OrthographicCamera _camera;

		bool _rotation;
		glm::vec3 _cameraPosition = {0.f, 0.f, 0.f};
		float _cameraRotation = 0.f;
		float _cameraTranslationSpeed = 5.0f, _cameraRotationSpeed = 180.0f;
	};
};

#pragma once
#include <Engine3D/Renderer2D/OrthographicCamera.h>
#include <Engine3D/Core/Timestep.h>
#include <Engine3D/Events/ApplicationEvent.h>
#include <Engine3D/Events/Event.h>
#include <Engine3D/Events/MouseEvent.h>


namespace Engine3D{
	// Knowing bounds of the camera itself.	
	struct OrthographicCameraBounds{
		OrthographicCameraBounds() = default;
		OrthographicCameraBounds(float _left, float _right, float _bottom, float _top) : left(_left), right(_right), bottom(_bottom), top(_top) {}

		float left;
		float right;
		float bottom;
		float top;

		float getWidth() { return right - left; }
		float getHeight() { return top - bottom; }
	};

	class OrthographicCameraController{
	public:	
		OrthographicCameraController(float aspectRatio, bool rotation=false); // vertically when camera starts up that there is 2 units of space (then to get correct aspect ratio, have: aspectratio * 2 units)
		
		void getProjection();
		
		void onUpdate(Timestep ts);
		void onEvent(Event& e);

		void onResize(float width, float height);

		OrthographicCamera& getCamera() { return _camera; }
		OrthographicCamera getCamera() const { return _camera; }

		const OrthographicCameraBounds& getBounds() const { return _bounds; }
		
		float getZoomLevel() const { return _zoomLevel; }
		void setZoomLevel(float level) {
			_zoomLevel = level;
			calculateView();
		}

	private:
		void calculateView();
		bool onMouseScrolled(MouseScrolledEvent& e);
		bool onWindowResized(WindowResizeEvent& e);

	private:
		float _aspectRatio;
		float _zoomLevel = 1.f; // Higher zoom level is, the further out you zoomed inwards.
		OrthographicCamera _camera;
		OrthographicCameraBounds _bounds;

		bool _rotation;
		glm::vec3 _cameraPosition = {0.f, 0.f, 0.f};
		float _cameraRotation = 0.f;
		float _cameraTranslationSpeed = 5.0f, _cameraRotationSpeed = 180.0f;
	};
};

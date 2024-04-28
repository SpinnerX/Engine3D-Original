#include <Engine3D/Engine3DPrecompiledHeader.h>
#include <Engine3D/Renderer2D/OrthographicCameraController.h>
#include <Engine3D/Events/InputPoll.h>
/* #include <Engine3D/Core/KeyCodes.h> */

namespace Engine3D{
	
	// Quick NOTE: Redundant and should probably change how we initialize, because for some reason _bounds keeps getting considered uninitialized when initializing  with constructor using : _bounds(...) 
	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation) : _aspectRatio(aspectRatio), _rotation(rotation), _camera(-_aspectRatio * _zoomLevel, _aspectRatio * _zoomLevel, -_zoomLevel, _zoomLevel){
        _bounds = OrthographicCameraBounds(-_aspectRatio * _zoomLevel, _aspectRatio * _zoomLevel, -_zoomLevel, _zoomLevel);
        _camera = OrthographicCamera(_bounds.left, _bounds.right, _bounds.bottom, _bounds.top);
	}

	// A way to control our cameras
	void OrthographicCameraController::onUpdate(Timestep ts){
		RENDER_PROFILE_FUNCTION();

        if(InputPoll::isKeyPressed(ENGINE_KEY_A)){ // RIGHT
			_cameraPosition.x -= std::cos(glm::radians(_cameraRotation)) * _cameraTranslationSpeed * ts;
			_cameraPosition.y -= std::sin(glm::radians(_cameraRotation)) * _cameraTranslationSpeed * ts;
        }
        else if(InputPoll::isKeyPressed(ENGINE_KEY_D)){ // LEFT
			_cameraPosition.x += std::cos(glm::radians(_cameraRotation)) * _cameraTranslationSpeed * ts;
			_cameraPosition.y += std::sin(glm::radians(_cameraRotation)) * _cameraTranslationSpeed * ts;
        }
        else if(InputPoll::isKeyPressed(ENGINE_KEY_W)){ // UP
			_cameraPosition.x += -std::sin(glm::radians(_cameraRotation)) * _cameraTranslationSpeed * ts;
			_cameraPosition.y += std::cos(glm::radians(_cameraRotation)) * _cameraTranslationSpeed * ts;
        }
        else if(InputPoll::isKeyPressed(ENGINE_KEY_S)){ // DOWN
			_cameraPosition.x -= -std::sin(glm::radians(_cameraRotation)) * _cameraTranslationSpeed * ts;
			_cameraPosition.y -= std::cos(glm::radians(_cameraRotation)) * _cameraTranslationSpeed * ts;
        }
		
		// Checking if we set the rotation speed
		if(_rotation){

			if(InputPoll::isKeyPressed(ENGINE_KEY_Q)){ // Rotate Right
				_cameraRotation -= _cameraRotationSpeed * ts;
			}

			if(InputPoll::isKeyPressed(ENGINE_KEY_E)){ // Rotate Left
				_cameraRotation += _cameraRotationSpeed * ts;
			}
			
			if(_cameraRotation > 180.0f)
				_cameraRotation -= 360.0f;
			else if(_cameraRotation <= -180.0f)
				_cameraRotation += 360.0f;

			// Then we set the camera rotation
			_camera.setRotation(_cameraRotation);
		}
		
		_camera.setPosition(_cameraPosition);
		_cameraTranslationSpeed = _zoomLevel;
	}

	void OrthographicCameraController::onEvent(Event& e){
		RENDER_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(Engine3D::bind(this, &OrthographicCameraController::onMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(Engine3D::bind(this, &OrthographicCameraController::onWindowResized));
	}
	
	void OrthographicCameraController::onResize(float width, float height){
		_aspectRatio = width / height;
		this->calculateView(); // recalculates the view when we change and resize the camera controller's w and h.
	}
		
	void OrthographicCameraController::calculateView(){
		_bounds = { -_aspectRatio * _zoomLevel, _aspectRatio * _zoomLevel, -_zoomLevel, _zoomLevel };
		_camera.setProjection(_bounds.left, _bounds.right, _bounds.bottom, _bounds.top);
	}
	
	
	bool OrthographicCameraController::onMouseScrolled(MouseScrolledEvent& e){
		RENDER_PROFILE_FUNCTION();

		_zoomLevel -= e.GetYOffset() * 0.25f; // Modify thihs const offset for window resized event event
		
		_zoomLevel = std::max(_zoomLevel, 0.25f); // This allows us to control our offsets for our zooming level, making sure we don't zoom too far our or zooming in too close.
		calculateView();
		return false;
	}

	bool OrthographicCameraController::onWindowResized(WindowResizeEvent& e){
		RENDER_PROFILE_FUNCTION();
		this->onResize((float)e.GetWidth(), (float)e.GetHeight());
		return false;
	}
};

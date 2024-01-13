#include <GameEnginePrecompiledHeader.h>
#include <GameEngine/Renderer/OrthographicCameraController.h>
#include <GameEngine/Core/InputPoll.h>
#include <GameEngine/Core/KeyCodes.h>

namespace RendererEngine{
	
	// Quick NOTE: Redundant and should probably change how we initialize, because for some reason _bounds keeps getting considered uninitialized when initializing  with constructor using : _bounds(...) 
	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation) : _aspectRatio(aspectRatio), _rotation(rotation), _camera(-_aspectRatio * _zoomLevel, _aspectRatio * _zoomLevel, -_zoomLevel, _zoomLevel){
        _bounds = OrthographicCameraBounds(-_aspectRatio * _zoomLevel, _aspectRatio * _zoomLevel, -_zoomLevel, _zoomLevel);
        _camera = OrthographicCamera(_bounds.left, _bounds.right, _bounds.bottom, _bounds.top);
	}

	// A way to control our cameras
	void OrthographicCameraController::onUpdate(Timestep ts){
		RENDER_PROFILE_FUNCTION();

        if(InputPoll::isKeyPressed(RENDER_KEY_A)){ // RIGHT
			_cameraPosition.x -= std::cos(glm::radians(_cameraRotation)) * _cameraTranslationSpeed * ts;
			_cameraPosition.y -= std::sin(glm::radians(_cameraRotation)) * _cameraTranslationSpeed * ts;
        }
        else if(InputPoll::isKeyPressed(RENDER_KEY_D)){ // LEFT
			_cameraPosition.x += std::cos(glm::radians(_cameraRotation)) * _cameraTranslationSpeed * ts;
			_cameraPosition.y += std::sin(glm::radians(_cameraRotation)) * _cameraTranslationSpeed * ts;
        }
        else if(InputPoll::isKeyPressed(RENDER_KEY_W)){ // UP
			_cameraPosition.x += -std::sin(glm::radians(_cameraRotation)) * _cameraTranslationSpeed * ts;
			_cameraPosition.y += std::cos(glm::radians(_cameraRotation)) * _cameraTranslationSpeed * ts;
        }
        else if(InputPoll::isKeyPressed(RENDER_KEY_S)){ // DOWN
			_cameraPosition.x -= -std::sin(glm::radians(_cameraRotation)) * _cameraTranslationSpeed * ts;
			_cameraPosition.y -= std::cos(glm::radians(_cameraRotation)) * _cameraTranslationSpeed * ts;
        }
		
		// Checking if we set the rotation speed
		if(_rotation){

			if(InputPoll::isKeyPressed(RENDER_KEY_Q)){ // Rotate Right
				_cameraRotation -= _cameraRotationSpeed * ts;
			}

			if(InputPoll::isKeyPressed(RENDER_KEY_E)){ // Rotate Left
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
		dispatcher.Dispatch<MouseScrolledEvent>(bind_function(this, &OrthographicCameraController::onMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(bind_function(this, &OrthographicCameraController::onWindowResized));
	}

	
	bool OrthographicCameraController::onMouseScrolled(MouseScrolledEvent& e){
		RENDER_PROFILE_FUNCTION();

		_zoomLevel -= e.GetYOffset() * 0.25f; // Modify thihs const offset for window resized event event
		
		_zoomLevel = std::max(_zoomLevel, 0.25f); // This allows us to control our offsets for our zooming level, making sure we don't zoom too far our or zooming in too close.
		_bounds = { -_aspectRatio * _zoomLevel, _aspectRatio * _zoomLevel, -_zoomLevel, _zoomLevel };
		_camera.setProjection(_bounds.left, _bounds.right, _bounds.bottom, _bounds.top);
		return false;
	}

	bool OrthographicCameraController::onWindowResized(WindowResizeEvent& e){
		RENDER_PROFILE_FUNCTION();
		_aspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		_bounds = { -_aspectRatio * _zoomLevel, _aspectRatio * _zoomLevel, -_zoomLevel, _zoomLevel };
		_camera.setProjection(_bounds.left, _bounds.right, _bounds.bottom, _bounds.top);
		return false;
	}
};

#include <GameEnginePrecompiledHeader.h>
#include <GameEngine/Renderer/OrthographicCameraController.h>
#include <GameEngine/Core/InputPoll.h>
#include <GameEngine/Core/KeyCodes.h>

namespace RendererEngine{
	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation) : _aspectRatio(aspectRatio), _camera(-_aspectRatio * _zoomLevel, _aspectRatio * _zoomLevel, -_zoomLevel, _zoomLevel), _rotation(rotation) {
	}

	// A way to control our cameras
	void OrthographicCameraController::onUpdate(Timestep ts){

        if(InputPoll::isKeyPressed(RENDER_KEY_D)){ // RIGHT
            _cameraPosition.x -= _cameraTranslationSpeed * ts;
        }
        else if(InputPoll::isKeyPressed(RENDER_KEY_A)){ // LEFT
            _cameraPosition.x += _cameraTranslationSpeed * ts;
        }
        else if(InputPoll::isKeyPressed(RENDER_KEY_W)){ // UP
            _cameraPosition.y -= _cameraTranslationSpeed * ts;
        }
        else if(InputPoll::isKeyPressed(RENDER_KEY_S)){ // DOWN
            _cameraPosition.y += _cameraTranslationSpeed * ts;
        }
		
		// Checking if we set the rotation speed
		if(_rotation){

			if(InputPoll::isKeyPressed(RENDER_KEY_Q)){ // Rotate Right
				_cameraRotation -= _cameraRotationSpeed * ts;
			}

			if(InputPoll::isKeyPressed(RENDER_KEY_E)){ // Rotate Left
				_cameraRotation += _cameraRotationSpeed * ts;
			}
			
			// Then we set the camera rotation
			_camera.setRotation(_cameraRotation);
		}
		
		_camera.setPosition(_cameraPosition);
		_cameraTranslationSpeed = _zoomLevel;
	}

	void OrthographicCameraController::onEvent(Event& e){
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(bind_function(this, &OrthographicCameraController::onMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(bind_function(this, &OrthographicCameraController::onWindowResized));
	}

	
	bool OrthographicCameraController::onMouseScrolled(MouseScrolledEvent& e){
		_zoomLevel -= e.GetYOffset() * 0.25f; // Modify thihs const offset for window resized event event
		
		// NOTE: When zooming too far out or too close, you eventually end up flipping your view upside down.
		_zoomLevel = std::max(_zoomLevel, 0.25f); // This allows us to control our offsets for our zooming level, making sure we don't zoom too far our or zooming in too close.
		_camera.setProjection(-_aspectRatio * _zoomLevel, _aspectRatio * _zoomLevel, -_zoomLevel, _zoomLevel);
		return false;
	}

	bool OrthographicCameraController::onWindowResized(WindowResizeEvent& e){
		_aspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		_camera.setProjection(-_aspectRatio * _zoomLevel, _aspectRatio * _zoomLevel, -_zoomLevel, _zoomLevel);
		return false;
	}
};

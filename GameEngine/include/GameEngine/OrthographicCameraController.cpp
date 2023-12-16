#include <GameEnginePrecompiledHeader.h>
#include <GameEngine/OrthographicCameraController.h>
#include <GameEngine/InputPoll.h>
#include <GameEngine/KeyCodes.h>

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

        if(InputPoll::isKeyPressed(RENDER_KEY_Q)){ // LEFT
            _cameraRotation += _cameraRotationSpeed * ts;
        }
        else if(InputPoll::isKeyPressed(RENDER_KEY_E)){ // RIGHT
            _cameraRotation -= _cameraRotationSpeed * ts;
        }
		
		_camera.setRotation(_cameraRotation);
		_camera.setPosition(_cameraPosition);
	}

	void OrthographicCameraController::onEvent(Event& e){
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(bind_function(this, &OrthographicCameraController::onMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(bind_function(this, &OrthographicCameraController::onWindowResized));
	}

	
	bool OrthographicCameraController::onMouseScrolled(MouseScrolledEvent& e){
		_zoomLevel -= e.GetYOffset();
		_camera.setProjection(-_aspectRatio * _zoomLevel, _aspectRatio * _zoomLevel, -_zoomLevel, _zoomLevel);
		return false;
	}

	bool OrthographicCameraController::onWindowResized(WindowResizeEvent& e){
		_aspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		_camera.setProjection(-_aspectRatio * _zoomLevel, _aspectRatio * _zoomLevel, -_zoomLevel, _zoomLevel);
		return false;
	}
};

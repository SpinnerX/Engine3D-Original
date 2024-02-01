#include <GameEnginePrecompiledHeader.h>
#include <GameEngine/Renderer/EditorCamera.h>
#include <GameEngine/Core/KeyCodes.h>
#include <GameEngine/Core/MouseButtonCodes.h>
#include <GameEngine/Core/InputPoll.h>
#include <GLFW/glfw3.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace RendererEngine{
    EditorCamera::EditorCamera(float fov, float aspectRatio, float nearClip, float farClip) 
		: _fov(fov), _aspectRatio(aspectRatio), _nearClip(nearClip), _farClip(farClip), Camera(glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip)){
		updateView();
	}
    
    void EditorCamera::onUpdate(Timestep ts){
		if(InputPoll::isKeyPressed(KeyCode::LeftAlt)){
			const glm::vec2& mouse = glm::vec2{InputPoll::getMouseX(), InputPoll::getMouseY()};

			glm::vec2 delta = (mouse - _initialMousePosition) * 0.003f;

			_initialMousePosition = mouse;

			if(InputPoll::isMouseButtonPressed(Mouse::ButtonMiddle))
				mousePan(delta);
			else if(InputPoll::isMouseButtonPressed(Mouse::ButtonLeft))
				mouseRotate(delta);
			else if(InputPoll::isMouseButtonPressed(Mouse::ButtonRight))
				mouseZoom(delta.y);
		}

		updateView();
	}

    void EditorCamera::onEvent(Event& e){
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(bind_function(this, &EditorCamera::onMouseScroll));
	}

    glm::vec3 EditorCamera::getUpDirection() const {
		return glm::rotate(getOrientation(), glm::vec3(0.0f, 1.0f, 0.0f));
	}
    
    glm::vec3 EditorCamera::getRightDirection() const{
		return glm::rotate(getOrientation(), glm::vec3(1.0f, 0.0f, 0.0f));
	}
    
    glm::vec3 EditorCamera::getForwardDirection() const{
		return glm::rotate(getOrientation(), glm::vec3(0.0f, 0.0f, -1.0f));
	}

    glm::quat EditorCamera::getOrientation() const{
		return glm::quat(glm::vec3(-_pitch, -_yaw, 0.0f));
	}

    void EditorCamera::updateProjection(){
		_aspectRatio = _viewportWidth / _viewportHeight;
		_projectionMatrix = glm::perspective(glm::radians(_fov), _aspectRatio, _nearClip, _farClip);
		updateView();
	}

    void EditorCamera::updateView(){
		_position = calculatePosition();
		
		glm::quat orientation = getOrientation();
		_viewMatrix = glm::translate(glm::mat4(1.0f), _position) * glm::toMat4(orientation);
		_viewMatrix = glm::inverse(_viewMatrix);
	}

    bool EditorCamera::onMouseScroll(MouseScrolledEvent& e){
		float delta = e.GetYOffset() * 0.1f;
		mouseZoom(delta);
		updateView();
		return false;
	}

    void EditorCamera::mousePan(const glm::vec2& delta){
		auto[xSpeed, ySpeed] = panSpeed();

		_focalPoint += -getRightDirection() * delta.x * xSpeed * _distance;
		_focalPoint += getUpDirection() * delta.y * ySpeed * _distance;
	}
    
    void EditorCamera::mouseRotate(const glm::vec2& delta){
		float yawSign = getUpDirection().y < 0 ? -1.0f : 1.0f;
		_yaw += yawSign * delta.x * rotationSpeed();
		_pitch += delta.y * rotationSpeed();
	}
    
    void EditorCamera::mouseZoom(float delta){
		_distance -= delta * zoomSpeed();

		if(_distance < 1.0f){
			_focalPoint += getForwardDirection();
			_distance = 1.0f;
		}
	}

    glm::vec3 EditorCamera::calculatePosition() const{
		return _focalPoint - getForwardDirection() * _distance;
	}

    std::pair<float, float> EditorCamera::panSpeed() const{
		float x = std::min(_viewportWidth / 1000.0f, 2.4f); // max = 2.4.f
		float xFactor = 0.0366f * (x * x) - 0.1778f * x + 0.3021f;
		
		float y = std::min(_viewportHeight / 1000.0f, 2.4f); // max = 2.4f
		float yFactor = 0.0366f * (y * y) - 0.1778f * y + 0.3021f;

		return {xFactor, yFactor};
	}
    
    float EditorCamera::rotationSpeed() const{ return 0.8f; }

    float EditorCamera::zoomSpeed() const{
		float distance = _distance * 0.2f;
		distance = std::max(distance, 0.0f);

		float speed = distance * distance;
		speed = std::min(speed, 100.0f);
		return speed;
	}
	
};

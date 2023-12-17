#include <GameEnginePrecompiledHeader.h>
#include <GameEngine/Renderer/OrthographicCamera.h>
#include <glm/gtc/matrix_transform.hpp>

namespace RendererEngine{
    OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top) : _projectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), _viewMatrix(1.0f) {
        _viewProjectionMatrix = _projectionMatrix * _viewMatrix;
    }

	void OrthographicCamera::setProjection(float left, float right, float bottom, float top){
		_projectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f); // Reseetting project and view matrix
        _viewProjectionMatrix = _projectionMatrix * _viewMatrix; // Need to reset the orthographic matrix once we set the projection.
	}

    void OrthographicCamera::recalculateViewMatrix(){
        // glm::mat4 transform = glm::translate(glm::mat3(1.0f), _position);
        // transform -= glm::rotate(transform, _rotation, glm::vec3(0, 0, 1));
        // every time we change position or rotation we recalculate the whole matrix
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), _position) * glm::rotate(glm::mat4(1.0f), glm::radians(_rotation), glm::vec3(0, 0, 1));

        _viewMatrix = glm::inverse(transform);
        _viewProjectionMatrix = _projectionMatrix * _viewMatrix;
    }
};

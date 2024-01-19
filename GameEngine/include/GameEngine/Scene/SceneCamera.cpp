#include <GameEnginePrecompiledHeader.h>
#include <GameEngine/Scene/SceneCamera.h>
#include <glm/gtc/matrix_transform.hpp>

namespace RendererEngine{

	
	SceneCamera::SceneCamera() {
		recalculateProjection();
	}

	void SceneCamera::setOrthographic(float size, float nearClip, float farClip){
		_orthographicSize = size;
		_orthographicNear = nearClip;
		_orthographicFar = farClip;
		recalculateProjection();
	}
	
	void SceneCamera::setViewportSize(uint32_t width, uint32_t height){
		_aspectRatio = (float)width / (float)height;
		recalculateProjection();
	}
	
	void SceneCamera::recalculateProjection(){
		float orthoLeft = -_orthographicSize * _aspectRatio * 0.5f;
		float orthoRight = _orthographicSize * _aspectRatio * 0.5f;
		float orthoBottom = -_orthographicSize * 0.5f;
		float orthoTop = _orthographicSize * 0.5f;

		_projectionMatrix = glm::ortho(orthoLeft, orthoRight, orthoBottom, orthoTop, _orthographicNear, _orthographicFar);
	}
};

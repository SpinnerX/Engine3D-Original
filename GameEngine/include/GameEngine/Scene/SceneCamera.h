#pragma once
#include <GameEngine/Renderer/Camera.h>

namespace RendererEngine{
	/*
	 *
	 * SceneCamera
	 * @note essentially going to be this camera derived.
	 * @note its just the Scene Camera will be specified to having parameters.
	 * @note including functionality such as supporting multiple camera views.
	 * @note other things that make up this scene camera.
	 * @note make sure to set viweportSize before rendering.
	 *
	 *
	 * */
	class SceneCamera : public Camera{
	public:
		SceneCamera();
		virtual ~SceneCamera() = default;
		
		void setOrthographic(float size, float nearClip, float farClip);

		void setViewportSize(uint32_t width, uint32_t height);
		
		float getOrthographicSize() const { return _orthographicSize; }

		void setOrthographicSize(float size) {
			_orthographicSize = size;
			recalculateProjection();
		}


	private:
		void recalculateProjection();

	private:
		float _orthographicSize = 10.0f;
		float _orthographicNear = -1.0f;
		float _orthographicFar = 1.0f;
		// When the viewport size gets changed the entire projection matrix needs to be recalculated.
		float _aspectRatio = 1.0f; // Need to keep track of viewport size.
	};
};

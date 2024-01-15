#pragma once
#include <glm/glm.hpp>

namespace RendererEngine{
	/*
	 *
	 * Camera class
	 * - Renderer kind of camera
	 * - Has a projection and view matrix.
	 * - Acts as the Camera Component, not the orthographic camera itself.
	 *
	 *
	 * */
	class Camera{
	public:
		Camera(const glm::mat4& projecMat) : _projectionMatrix(projecMat) {}

		const glm::mat4& getProjection() const { return _projectionMatrix; }

	private:
		glm::mat4 _projectionMatrix;
	};
};

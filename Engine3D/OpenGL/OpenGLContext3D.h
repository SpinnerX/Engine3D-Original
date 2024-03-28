#pragma once
#include <Engine3D/Core/core.h>
#include <Engine3D/interfaces/GraphicsContext.h>

namespace Engine3D{

	class OpenGLContext3D : public GraphicsContext{
	public:
		virtual ~OpenGLContext3D(){}

		virtual void Init() override;

		virtual void swapBuffers() override;
	};
};

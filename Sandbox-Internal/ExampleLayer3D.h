#pragma once
#include <Engine3D/Core/Layer.h>
#include <Engine3D/OpenGL/OpenGLBuffer3D.h>

namespace Engine3D{
	class ExampleLayer3D : public Layer{
	public:
		ExampleLayer3D() = default;

		void onAttach() override {
			float data[10] = {};
			vertexBuffer = VertexBuffer3D::Create<sizeof(data)>(data);
		}

		void onDetach() override {}

		void onUpdate(Timestep ts) override {}

		void onEvent(Event& e) override {}
		
		void onImguiRender() override {}

	private:
		Ref<VertexBuffer3D> vertexBuffer;
	};
};

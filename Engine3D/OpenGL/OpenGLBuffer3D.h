#pragma once
#include <Engine3D/Core/core.h>
#include <Engine3D/interfaces/Buffer.h>

namespace Engine3D{
	/*
	 * @file OpenGLBuffer3D.h
	 * @note OpenGL requires that when a buffer is given data
	 * @note Those vertices data are to be binded/ubinded
	 * @note Before rendering
	 *
	*/

	class OpenGLVertexBuffer3D : public VertexBuffer3D{
	public:
		OpenGLVertexBuffer3D(void* data, uint32_t size);
		OpenGLVertexBuffer3D(uint32_t size);

		virtual ~OpenGLVertexBuffer3D();

		virtual void bind() const override;
		virtual void unbind() const override;

		virtual void setLayout(const BufferLayout& layout) override{
			_layout = layout;
		}
		
		template<typename T, auto SIZE>
		void setData(T* data){
			setData(data, SIZE);
		}

	private:
		virtual void setData(const void* data, uint32_t size) override;
		
	private:
		uint32_t _rendererID;
		BufferLayout _layout;
	};
};

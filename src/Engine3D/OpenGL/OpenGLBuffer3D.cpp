#include <Engine3D/Engine3DPrecompiledHeader.h>
#include <Engine3D/OpenGL/OpenGLBuffer3D.h>

namespace Engine3D{
	
	OpenGLVertexBuffer3D::OpenGLVertexBuffer3D(void* data, uint32_t size){
		glGenBuffers(1, &_rendererID);
		glBindBuffer(GL_ARRAY_BUFFER, _rendererID);
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer3D::OpenGLVertexBuffer3D(uint32_t size){
		glGenBuffers(1, &_rendererID);
		glBindBuffer(GL_ARRAY_BUFFER, _rendererID);
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
	}

	OpenGLVertexBuffer3D::~OpenGLVertexBuffer3D(){
		glDeleteBuffers(1, &_rendererID);
	}

	void OpenGLVertexBuffer3D::bind() const {
		glBindBuffer(1, _rendererID);
	}

	void OpenGLVertexBuffer3D::unbind() const {
		glBindBuffer(GL_ARRAY_BUFFER, _rendererID);
	}

	void OpenGLVertexBuffer3D::setData(const void* data, uint32_t size){
		glBindBuffer(GL_ARRAY_BUFFER, _rendererID);
		glBufferSubData (GL_ARRAY_BUFFER, 0, size,  data);
	}

};

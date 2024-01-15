#include <GameEnginePrecompiledHeader.h>
#include <GameEngine/Renderer/Framebuffer.h>
#include <GameEngine/platforms/OpenGL/OpenGLFramebuffer.h>
#include <glad/glad.h>

namespace RendererEngine{

	OpenGLFrameBuffer::OpenGLFrameBuffer(const FrameBufferSpecifications& specs) : _specifications(specs){
		invalidate();
	}

	OpenGLFrameBuffer::~OpenGLFrameBuffer(){
		glDeleteFramebuffers(1, &_rendererID);
		glDeleteTextures(1, &_colorAttachments);
		glDeleteTextures(1, &_depthAttachments);
	}

	void OpenGLFrameBuffer::invalidate(){
		
		// Validating if the renderer ID has already been set.
		if(!_rendererID){
			glDeleteFramebuffers(1, &_rendererID);
			glDeleteTextures(1, &_colorAttachments);
			glDeleteTextures(1, &_depthAttachments);
		}

		// Quick NOTE: glCreateFramebuffers and glCreateTextures work on OpenGL 4.5 and versions afterwards
		/* glCreateFramebuffers(1, &_rendererID); */
		glGenFramebuffers(1, &_rendererID);

		glBindFramebuffer(GL_FRAMEBUFFER, _rendererID);


		/* glCreateTextures(GL_TEXTURE_2D, 1, &_colorAttachments); */
		glGenTextures(1, &_colorAttachments);
		glBindTexture(GL_TEXTURE_2D, _colorAttachments);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _specifications.width, _specifications.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _colorAttachments, 0);

		/* glCreateTextures(GL_TEXTURE_2D, 1, &_depthAttachments); */
		glGenTextures(1, &_depthAttachments);
		glBindTexture(GL_TEXTURE_2D, _depthAttachments);

		/* glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, _specifications.width, _specifications.height); */

		// Uncomment this if glTexStorage2D doesn't work.
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, _specifications.width, _specifications.height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, _depthAttachments, 0);

		if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){	
			coreLogError("Framebuffer is incomplete!");
			render_core_assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "FrameBuffer is incomplete!");
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFrameBuffer::bind() {
		glBindFramebuffer(GL_FRAMEBUFFER, _rendererID);	
		glViewport(0, 0, _specifications.width, _specifications.height);
	}

	void OpenGLFrameBuffer::unbind() {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFrameBuffer::resize(uint32_t w, uint32_t h){
		_specifications.width = w;
		_specifications.height = h;
		this->invalidate();
	}

};

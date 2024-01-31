#include <GameEnginePrecompiledHeader.h>
#include <GameEngine/Renderer/Framebuffer.h>
#include <GameEngine/platforms/OpenGL/OpenGLFramebuffer.h>
#include <glad/glad.h>

namespace RendererEngine{
	static const uint32_t maxFrameBufferSize = 8192;

	static GLenum textureTarget(bool multisample){
		return multisample ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;
	}

	static bool isDepth(FrameBufferTextureFormat format){
		if(format == FrameBufferTextureFormat::DEPTH24STENCIL8) return true;

		return false;
	}

	OpenGLFrameBuffer::OpenGLFrameBuffer(const FrameBufferSpecifications& specs) : _specifications(specs){
		if(specs.attachments.attachments.size() <= 0){
			assert(specs.attachments.attachments.size() > 0);
		}

		for(auto spec : specs.attachments.attachments){
			attachmentFormats.push_back(spec.textureFormat);
			if(!isDepth(spec.textureFormat)){
				colorAttachments.emplace_back(std::move(spec));
			}
			else{
				depthAttachmentAttachmentSpec = std::move(spec);
			}
		}

		invalidate();
	}

	OpenGLFrameBuffer::~OpenGLFrameBuffer(){
		glDeleteFramebuffers(1, &_rendererID);
		for(auto spec : _specifications.attachments.attachments){
			glDeleteTextures(1, &spec.attachmentID);
		}

		glDeleteTextures(1, &depthAttachmentAttachmentSpec.attachmentID);
		colorAttachments.clear();
	}

	void OpenGLFrameBuffer::invalidate(){
		
		// Validating if the renderer ID has already been set.
		if(!_rendererID){
			glDeleteFramebuffers(1, &_rendererID);
		}

		// Quick NOTE: glCreateFramebuffers and glCreateTextures work on OpenGL 4.5 and versions afterwards
		/* glCreateFramebuffers(1, &_rendererID); */
		glGenFramebuffers(1, &_rendererID);

		glBindFramebuffer(GL_FRAMEBUFFER, _rendererID);

		if(depthAttachmentAttachmentSpec.textureFormat == FrameBufferTextureFormat::None){
			return;
		}

		bool multisample = _specifications.samples > 1;

		// Color Attachments
		if(colorAttachments.size() > 0){
			for(size_t i = 0; i < colorAttachments.size(); i++){
				glGenTextures(1, &colorAttachments[i].attachmentID);
				glBindTexture(GL_TEXTURE_2D, colorAttachments[i].attachmentID);
				
				/* colorAttachment(textureTarget(multisample), colorAttachments[i].attachmentID, textureTarget(multisample)); */
				/* glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _specifications.width, _specifications.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr); */
				/* glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); */
				/* glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); */
				/* glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE); */
				/* glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); */
				/* glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); */
				
				if(multisample){
					glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, _specifications.samples, GL_RGBA8, _specifications.width, _specifications.height, GL_FALSE);
				}
				else{
					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _specifications.width, _specifications.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
					
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				}


				/* glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorAttachments[i].attachmentID, 0); */
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, textureTarget(multisample), colorAttachments[i].attachmentID, 0);
			}
		}

		// Depth attachment
		if(depthAttachmentAttachmentSpec.textureFormat != FrameBufferTextureFormat::None){
			glGenTextures(1, &depthAttachmentAttachmentSpec.attachmentID);
			glBindTexture(GL_TEXTURE_2D, depthAttachmentAttachmentSpec.attachmentID);

			if(multisample){
					glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, _specifications.samples, GL_DEPTH24_STENCIL8, _specifications.width, _specifications.height, GL_FALSE);
			}
			else{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, _specifications.width, _specifications.height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			}

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, textureTarget(multisample), depthAttachmentAttachmentSpec.attachmentID, 0);
		}
		
		if(colorAttachments.size() > 1){
			GLenum buffers[4] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3};
			glDrawBuffers(colorAttachments.size(), buffers);
		}
		else if(colorAttachments.empty()){
			glDrawBuffer(GL_NONE);
		}

		if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){	
			coreLogError("Framebuffer is incomplete!");
			render_core_assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "FrameBuffer is incomplete!");
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	
	void OpenGLFrameBuffer::colorAttachment(GLenum target, uint32_t& attachmentID, GLenum format){
		glTexImage2D(target, 0, format, _specifications.width, _specifications.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		
	}

	void OpenGLFrameBuffer::bind() {
		glBindFramebuffer(GL_FRAMEBUFFER, _rendererID);	
		glViewport(0, 0, _specifications.width, _specifications.height);
	}

	void OpenGLFrameBuffer::unbind() {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFrameBuffer::resize(uint32_t w, uint32_t h){
		if(w == 0 || h == 0 || w > maxFrameBufferSize || h > maxFrameBufferSize){
			coreLogError("Attempted to resize frame buffer to (w={}, h={})", w, h);
			return;
		}

		_specifications.width = w;
		_specifications.height = h;
		this->invalidate();
	}

};


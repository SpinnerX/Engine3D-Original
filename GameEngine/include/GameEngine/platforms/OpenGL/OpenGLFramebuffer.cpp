#include <GameEnginePrecompiledHeader.h>
#include <GameEngine/Renderer/Framebuffer.h>
#include <GameEngine/platforms/OpenGL/OpenGLFramebuffer.h>
#include <glad/glad.h>

namespace RendererEngine{
	static const uint32_t maxFrameBufferSize = 8192;
	namespace Utils{
		
		static GLenum TextureTarget(bool multisampled){
			return multisampled ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;
		}

		static void createTexture(bool multisampled, uint32_t* outID, uint32_t count){

			/* @note in opengl 4.5 and higher you can use th glCreateTextures function */
			/* glCreateTextures(TextureTarget(multisampled), count, outID); */
			glGenTextures(count, outID);
			/* glCreateTextures(TextureTarget(multisampled), count, outID); */


		}

		static void bindTexture(bool multisampled, uint32_t id){
			glBindTexture(TextureTarget(multisampled), id);
		}

		static bool isDepthFormat(FrameBufferTextureFormat format){
			switch (format) {
				case FrameBufferTextureFormat::DEPTH24STENCIL8: return true;
			}

			return false;
		}

		static void attachColorTexture(uint32_t id, int samples, GLenum format,uint32_t width, uint32_t height, int index){
			bool isMultiSample = samples > 1;

			if(isMultiSample){ // @note if not multisampled texture
				glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, format, width, height, GL_FALSE);
			}
			else{
				glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, GL_RGBA8, GL_UNSIGNED_BYTE, nullptr);
				/* glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); */
				/* glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); */
				/* glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE); */
				/* glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); */
				/* glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); */

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			}

			/* glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, GL_TEXTURE_2D, TextureTarget(isMultiSample), id, 0); */
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, TextureTarget(isMultiSample), id, 0);
		}
		
		static void attachDepthTexture(uint32_t id, int samples, GLenum format, GLenum attachmentType, uint32_t width, uint32_t height){
			bool isMultiSample = samples > 1;

			if(isMultiSample){ // @note if not multisampled texture
				glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, format, width, height, GL_FALSE);
			}
			else{
				// @note this glTexStorage2D is going to segfault, so instead use glTexImage2D (if on Mac)
				/* glTexStorage2D(GL_TEXTURE_2D, 1, format, width, height); */

				// Uncomment this if glTexStorage2D above doesn't work
				/* glTexImage2D(GL_TEXTURE_2D, 1, format, width, height, 0, format, GL_UNSIGNED_BYTE, nullptr); */
				glTexImage2D(GL_TEXTURE_2D, 0, format, width, height,0, format, GL_UNSIGNED_BYTE, NULL);
				/* glTexImage2D(GL_TEXTURE_2D, 1, format, width, height, 0, format, GL_UNSIGNED_INT_24_8, NULL); // This is the line to uncomment.. */
				/* glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, width, height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL); */
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			}

			glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, TextureTarget(isMultiSample), id, 0);
		}

	};

	OpenGLFrameBuffer::OpenGLFrameBuffer(const FrameBufferSpecifications& specs) : _specifications(specs){

		for(auto spec : _specifications.attachments.attachments){

			// @note if color attachment is not depth format then dont color attach it.
			// @note upon construction checking through list of formats to check the format for color and depth.
			if(!Utils::isDepthFormat(spec._textureFormat)){
				_colorAttachmentsSpecs.emplace_back(spec);
			}
			else{
				_depthAttachmentAttachmentSpecs = spec;
			}
		}

		invalidate();
	}

	OpenGLFrameBuffer::~OpenGLFrameBuffer(){
		glDeleteFramebuffers(1, &_rendererID);
		/* glDeleteTextures(1, &_colorAttachment); */
		glDeleteTextures(_colorAttachments.size(), _colorAttachments.data());
		glDeleteTextures(1, &_depthAttachment);
	}

	void OpenGLFrameBuffer::invalidate(){
		
		// Validating if the renderer ID has already been set.
		if(_rendererID){
			glDeleteFramebuffers(1, &_rendererID);
			glDeleteTextures(_colorAttachments.size(), _colorAttachments.data());
			glDeleteTextures(1, &_depthAttachment);

			_colorAttachments.clear(); // @note clearing the renderer id's
			_depthAttachment = 0;
		}

		// Quick NOTE: glCreateFramebuffers and glCreateTextures work on OpenGL 4.5 and versions afterwards
		/* glCreateFramebuffers(1, &_rendererID); */
		glGenFramebuffers(1, &_rendererID);

		glBindFramebuffer(GL_FRAMEBUFFER, _rendererID);

		// @note Attaching a Color buffer
		// @note this code below is where the attachments are being done.
		// @note sorting attachments from depth to color.
		bool isMultiSample = _specifications.samples > 1;

		if(_colorAttachmentsSpecs.size()){
			_colorAttachments.resize(_colorAttachmentsSpecs.size());

			Utils::createTexture(isMultiSample, _colorAttachments.data(), _colorAttachments.size()); // @note to generate bunch of ID's for each color attachment in one go.
			
			// @note going through all our attachments and binding them with a multisampled with their RendererID's (i is renderer id).
			for(size_t i = 0; i < _colorAttachments.size(); i++){
				Utils::bindTexture(isMultiSample, _colorAttachments[i]);

				switch (_colorAttachmentsSpecs[i]._textureFormat) {
					case RendererEngine::FrameBufferTextureFormat::RGBA8:
						Utils::attachColorTexture(_colorAttachments[i], _specifications.samples, GL_RGBA8, _specifications.width, _specifications.height, i);
						break;
				}
			}
		}


		if(_depthAttachmentAttachmentSpecs._textureFormat != FrameBufferTextureFormat::None){
			Utils::createTexture(isMultiSample, &_depthAttachment, 1);
			Utils::bindTexture(isMultiSample, _depthAttachment);

			switch (_depthAttachmentAttachmentSpecs._textureFormat) {
			case RendererEngine::FrameBufferTextureFormat::DEPTH24STENCIL8:
				Utils::attachDepthTexture(_depthAttachment, _specifications.samples, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT, _specifications.width, _specifications.height);
				break;
			}
		}

		if(_colorAttachments.size() > 1){
			render_core_assert(_colorAttachments.size() <= 3);
			GLenum buffers[4] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3};

			glDrawBuffers(_colorAttachments.size(), buffers);
		}
		else if(_colorAttachments.empty()){
			glDrawBuffer(GL_NONE);
		}

		render_core_assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "FrameBuffer is incomplete!");

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
		if(w == 0 || h == 0 || w > maxFrameBufferSize || h > maxFrameBufferSize){
			coreLogError("Attempted to resize frame buffer to (w={}, h={})", w, h);
			return;
		}

		_specifications.width = w;
		_specifications.height = h;
		this->invalidate();
	}

};

#pragma once
#include <GameEngine/Renderer/Framebuffer.h>

namespace RendererEngine{

	class OpenGLFrameBuffer : public FrameBuffer{
	public:
		OpenGLFrameBuffer(const FrameBufferSpecifications& specs);
		virtual ~OpenGLFrameBuffer();

		void bind() override;
		void unbind() override;
		
		virtual void resize(uint32_t w, uint32_t h) override;
		
		virtual const FrameBufferSpecifications& getSpecifications() const override { return _specifications; }
		virtual uint32_t getColorAttachmentRendererID(uint32_t index=0) const override { render_core_assert(index < _colorAttachments.size()); return _colorAttachments[index]; }
		
		// @function invalidate
		// @note means that something has been changed/modified inside the frame buffer.
		// @note meaning it is no longer valid.
		void invalidate();

	private:
		uint32_t _rendererID;
		/* uint32_t _colorAttachment = 0; */
		/* uint32_t _depthAttachment = 0; //  May delete this later */
		FrameBufferSpecifications _specifications;

		std::vector<FrameBufferTextureSpecifications> _colorAttachmentsSpecs;
		FrameBufferTextureSpecifications _depthAttachmentAttachmentSpecs = FrameBufferTextureFormat::None; // Keeping track of state.
		std::vector<uint32_t> _colorAttachments;
		uint32_t _depthAttachment = 0;
	};
};

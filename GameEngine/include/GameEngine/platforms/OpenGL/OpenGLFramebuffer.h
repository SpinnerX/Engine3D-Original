#pragma once
#include <GameEngine/Renderer/Framebuffer.h>

namespace RendererEngine{

	class OpenGLFrameBuffer : public FrameBuffer{
	public:
		OpenGLFrameBuffer(const FrameBufferSpecifications& specs);
		virtual ~OpenGLFrameBuffer();

		void bind() override;
		void unbind() override;
		
		virtual const FrameBufferSpecifications& getSpecifications() const override { return _specifications; }
		virtual uint32_t getColorAttachmentRendererID() const override { return _colorAttachments; }

		void invalidate();

	private:
		uint32_t _rendererID;
		uint32_t _colorAttachments;
		uint32_t _depthAttachments;
		FrameBufferSpecifications _specifications;
	};
};

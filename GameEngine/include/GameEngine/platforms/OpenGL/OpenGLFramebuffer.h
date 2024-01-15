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
		virtual uint32_t getColorAttachmentRendererID() const override { return _colorAttachments; }

		void invalidate();

	private:
		uint32_t _rendererID;
		uint32_t _colorAttachments = 0;
		uint32_t _depthAttachments = 0;
		FrameBufferSpecifications _specifications;
	};
};

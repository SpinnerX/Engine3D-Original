#pragma once
#include <GameEngine/Renderer/Framebuffer.h>

namespace RendererEngine {

	class OpenGLFrameBuffer : public FrameBuffer{
	public:
		OpenGLFrameBuffer(const FrameBufferSpecifications& specs);
		virtual ~OpenGLFrameBuffer();

		void bind() override;
		void unbind() override;

		virtual void resize(uint32_t w, uint32_t h) override;

		virtual const FrameBufferSpecifications& getSpecifications() const override;
	private:
		uint32_t _rendererID;

		FrameBufferSpecifications _specifications;
	};
}

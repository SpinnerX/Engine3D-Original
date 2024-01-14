#pragma once
#include <GameEngine/Core/core.h>

namespace RendererEngine{
	
	// FrameBuffer specifications (POD)
	struct FrameBufferSpecifications{
		uint32_t width, height;
		uint32_t samples = 1;

		// Basically say that this frame buffer is supposed to be rendering to this swap chain
		// Other words, equivalent to OpenGL's glBindFrameBuffer(0);
		// Telling to render this frame buffer onto this screen.
		// Allowing to create a frame buffer that might not exist

		// ** RendererPass **
		// * Utilizes a frame buffer 
		// * Frame buffer that contains a target
		// * Rendering to a screen means you might not have a frame buffer.
		bool swapChainTarget = false; 
	};

	class FrameBuffer{
	public:
		static Ref<FrameBuffer> Create(const FrameBufferSpecifications& specs);
		
		virtual void bind() = 0;
		virtual void unbind() = 0;

		virtual uint32_t getColorAttachmentRendererID() const = 0;
		
		virtual const FrameBufferSpecifications& getSpecifications() const = 0;
	};
};

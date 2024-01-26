#pragma once
#include <GameEngine/Core/core.h>

namespace RendererEngine{
	/*
	 *
	 * @function enum class FrameBufferTextureFormat
	 *
	 * @note handle different formatting types for color attachments
	 *
	 *
	 * */
	enum class FrameBufferTextureFormat{
		None=0,
		RGBA8,
		DEPTH24STENCIL8, // Depth/Stencil
		DEPTH=DEPTH24STENCIL8
	};
	
	/*
	 *
	 * @function FrameBufferTextureSpecifications
	 *
	 * @note struct that will contain the actual texture specs.
	 * @note containing the actual physical specification for textures.
	 *
	 *
	 * */

	struct FrameBufferTextureSpecifications{
		FrameBufferTextureSpecifications()  = default;
		FrameBufferTextureSpecifications(FrameBufferTextureFormat format) : _textureFormat(format){}

		FrameBufferTextureFormat _textureFormat = FrameBufferTextureFormat::None;
		// @note TODO: filtering/wrap
	};
	/*
	 *
	 * @function FrameBufferAttachmentSpecification
	 * @param std::vector<FrameBufferTextureSpecifications> is a list of the texture attachments themselves
	 * @note is the collective frame buffer attachments 
	 *
	 *
	 *
	 * */
	struct FrameBufferAttachmentSpecification{
		FrameBufferAttachmentSpecification(const std::initializer_list<FrameBufferTextureSpecifications>& list) : attachments(list){}

		std::vector<FrameBufferTextureSpecifications> attachments;
	};
	
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

		FrameBufferAttachmentSpecification attachments;
	};

	class FrameBuffer{
	public:
		virtual ~FrameBuffer() = default;
		static Ref<FrameBuffer> Create(const FrameBufferSpecifications& specs);
		
		virtual void bind() = 0;
		virtual void unbind() = 0;
		
		// Used for when we want to resize this buffer when running in another scene.
		virtual void resize(uint32_t w, uint32_t h) = 0;

		virtual uint32_t getColorAttachmentRendererID(uint32_t index = 0) const = 0;
		
		virtual const FrameBufferSpecifications& getSpecifications() const = 0;
	};
};

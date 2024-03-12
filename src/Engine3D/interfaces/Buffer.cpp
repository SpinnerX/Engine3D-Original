#include <Engine3D/Engine3DPrecompiledHeader.h>
#include <Engine3D/interfaces/Buffer.h>
#include <Engine3D/Renderer/Renderer.h>
#include <OpenGL/OpenGLBuffer.h>

namespace Engine3D{

    // Now use these functions to decide which renderer API's that we want to use
    // - such as which class to instantiate and utilize.
    Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size){
        switch (RendererAPI::getAPI()){
        case RendererAPI::API::None:
            render_core_assert(false, "RenderAPI::None is currently not supported!");
            return nullptr;
        case RendererAPI::API::OpenGL:
            return CreateRef<OpenGLVertexBuffer>(vertices, size);
        }
        render_core_assert(false, "Unknown renderer API");
        return nullptr;
    }

	Ref<VertexBuffer> VertexBuffer::Create(uint32_t size){
        switch (RendererAPI::getAPI()){
        case RendererAPI::API::None:
            render_core_assert(false, "RenderAPI::None is currently not supported!");
            return nullptr;
        case RendererAPI::API::OpenGL:
            return CreateRef<OpenGLVertexBuffer>(size);
        }
        render_core_assert(false, "Unknown renderer API");
        return nullptr;
		
	}

    Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t size){
        switch (RendererAPI::getAPI()){
        case RendererAPI::API::None:
            render_core_assert(false, "RenderAPI::None is currently not supported!");
            return nullptr;
        case RendererAPI::API::OpenGL:
            return CreateRef<OpenGLIndexBuffer>(indices, size);
        }
        render_core_assert(false, "Unknown renderer API");
        return nullptr;
    }
};

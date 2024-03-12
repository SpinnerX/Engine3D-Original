#include <Engine3D/interfaces/VertexArray.h>
#include <Engine3D/Renderer/Renderer.h>
#include <OpenGL/OpenGLVertexArray.h>

namespace Engine3D{

    Ref<VertexArray> VertexArray::Create(){
        switch (RendererAPI::getAPI()){
        case RendererAPI::API::None:
            render_core_assert(false, "RenderAPI::None is currently not supported!");
            return nullptr;
        case RendererAPI::API::OpenGL:
            return std::make_shared<OpenGLVertexArray>();
        }

        render_core_assert(false, "Unknown renderer API");
        return nullptr;
    }
};

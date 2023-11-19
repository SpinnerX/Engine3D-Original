#pragma once
#include <GameEngine/Layer.h>
#include <imgui/imgui.h>

namespace RendererEngine{

    // - This is going to be ImGuiLayer that will come with the engine
    //   to just start rendering debugging stuff or the debugger layer on top of the scene
    class RENDER_API ImGuiLayer : public Layer{
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        void onAttach();
        void onDetach();

        void onUpdate();

        virtual void onEvent(Event& event) override;

        std::string toString() const {
            std::stringstream ss;
            ss << "Vendor graphic card: " << glGetString(GL_VENDOR) << '\n';
            ss << "Renderer: " << glGetString(GL_RENDERER) << '\n';
            ss << "Version GL: " << glGetString(GL_VERSION) << '\n';
            ss << "Version GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION);
            return ss.str();
        }

        friend std::ostream& operator<<(std::ostream& outs, ImGuiLayer& layer){
            return outs << layer.toString();
        }

    private:
        float _time=0.f;
        // ImGuiContext* currentCtx;
    };
};
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

    private:
        float _time=0.f;
        // ImGuiContext* currentCtx;
    };
};
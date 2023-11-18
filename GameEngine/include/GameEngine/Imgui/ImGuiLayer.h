#pragma once
#include <GameEngine/Layer.h>

namespace RendererEngine{

    // - This is going to be ImGuiLayer that will come with the engine
    //   to just start rendering debugging stuff or the debugger layer on top of the scene
    class RENDER_API ImGuiLayer : public Layer{
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        virtual void onAttach() override;
        virtual void onDetach() override;

        virtual void onUpdate() override;

        virtual void onEvent(Event& event) override;

    private:
        float _time=0.f;
    };
};
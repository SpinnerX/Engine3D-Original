#pragma once
#include <GameEngine/Core/InputPoll.h>

namespace RendererEngine{
    class WindowsInput : public InputPoll{
    protected:
        bool isKeyPressedImpl(KeyCode keycode) override;

        bool isMouseButtonPressedImpl(MouseCode button) override;

        float getMouseXImpl() override;
        float getMouseYImpl() override;

        MousePosition getMousePositionImpl() override;
    };
};

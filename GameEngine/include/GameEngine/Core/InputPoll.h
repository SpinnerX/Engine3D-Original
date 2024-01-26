#pragma once
#include <GameEngine/Core/core.h>
#include <GameEngine/Core/KeyCodes.h>
#include <GameEngine/Core/MouseButtonCodes.h>
#include <glm/glm.hpp>

// InputPoll is going to be static
// - Where in a sense that there is going to be only one global input kind of manager
// - InputPoll is an interface allowing users to their own input poll systems
// - That can be used to check if a key or multiple keys has been pressed.

namespace RendererEngine{
    struct MousePosition{
        float xpos = 0.f;
        float ypos = 0.f;
    };

    class RENDER_API InputPoll{
    public:
        // Taking in a key and checking if it has been pressed
        // creating a singletone called _instance
        // This calls the implementation for Key Pressed that is implemented in WindowsInput
        static bool isKeyPressed(KeyCode keycode);
        static bool isMouseButtonPressed(MouseCode button);
        static glm::vec2 getMousePosition();
        static float getMouseX();
        static float getMouseY();
    };
};

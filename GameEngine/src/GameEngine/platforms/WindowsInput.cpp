#include <GameEnginePrecompiledHeader.h>
#include <GameEngine/Core/Application.h>
#include <GameEngine/Core/InputPoll.h>
#include <GLFW/glfw3.h>
#include <GameEngine/Core/MouseButtonCodes.h>

namespace RendererEngine{

    bool InputPoll::isKeyPressed(KeyCode keycode){
        // This will call GLFW and do everything needed when a key has been pressed
        auto window = static_cast<GLFWwindow *>(Application::Get().GetWindow().getNativeWindow());
		auto state = glfwGetKey(window, static_cast<int32_t>(keycode));

        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    // Handling mouse pressing events
    // and handling mouse cursor location
    bool InputPoll::isMouseButtonPressed(MouseCode button) {
        auto window = static_cast<GLFWwindow *>(Application::Get().GetWindow().getNativeWindow());
		auto state = glfwGetMouseButton(window, static_cast<int32_t>(button));

        return state == GLFW_PRESS;
    }

    float InputPoll::getMouseX() {
        auto[x, y] = getMousePosition();

        return x;
    }

    float InputPoll::getMouseY() {
        auto[x, y] = getMousePosition();

        return y;
    }

    MousePosition InputPoll::getMousePosition(){
        auto window = static_cast<GLFWwindow *>(Application::Get().GetWindow().getNativeWindow());
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        MousePosition position = {(float)xpos, (float)ypos};
        return position;
    }

};

#include <GameEnginePrecompiledHeader.h>
#include <GameEngine/Core/Application.h>
#include <GameEngine/platforms/Windows/WindowsInput.h>
#include <GLFW/glfw3.h>
#include <GameEngine/Core/MouseButtonCodes.h>

namespace RendererEngine{
    Scope<InputPoll> InputPoll::_instance = CreateScope<WindowsInput>();

    bool WindowsInput::isKeyPressedImpl(KeyCode keycode){
        // This will call GLFW and do everything needed when a key has been pressed
        auto window = static_cast<GLFWwindow *>(Application::Get().GetWindow().getNativeWindow());
		auto state = glfwGetKey(window, static_cast<int32_t>(keycode));

        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    // Handling mouse pressing events
    // and handling mouse cursor location
    bool WindowsInput::isMouseButtonPressedImpl(MouseCode button) {
        auto window = static_cast<GLFWwindow *>(Application::Get().GetWindow().getNativeWindow());
		auto state = glfwGetMouseButton(window, static_cast<int32_t>(button));

        return state == GLFW_PRESS;
    }

    float WindowsInput::getMouseXImpl() {
        auto[x, y] = getMousePositionImpl();

        return x;
    }

    float WindowsInput::getMouseYImpl() {
        auto[x, y] = getMousePositionImpl();

        return y;
    }

    MousePosition RendererEngine::WindowsInput::getMousePositionImpl(){
        auto window = static_cast<GLFWwindow *>(Application::Get().GetWindow().getNativeWindow());
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        MousePosition position = {(float)xpos, (float)ypos};
        return position;
    }

};

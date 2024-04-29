// #include <Engine3D/Engine3DPrecompiledHeader.h>
// #include <Engine3D/OpenGL/OpenGLInputPoll.h>

// namespace Engine3D{
// 	InputPoll* InputPoll::_instance = new OpenGLInputPoll();

// 	bool OpenGLInputPoll::isKeyPressedImpl(Key keycode){
// 		auto window = static_cast<GLFWwindow *>(Application::Get().GetWindow().getNativeWindow());

// 		auto state = glfwGetKey(window, static_cast<int32_t>(keycode));

// 		return state == GLFW_PRESS || state == GLFW_REPEAT;
// 	}

// 	bool OpenGLInputPoll::isMouseButtonPressedImpl(Mouse button){
// 		auto window = static_cast<GLFWwindow *>(Application::Get().GetWindow().getNativeWindow());

// 		auto state = glfwGetMouseButton(window, static_cast<int32_t>(button));

// 		return state == GLFW_PRESS;
// 	}

// 	float OpenGLInputPoll::getMouseXImpl(){
// 		auto[x, y] = getMousePositionImpl();
// 		return x;
// 	}

// 	float OpenGLInputPoll::getMouseYImpl(){
// 		auto[x, y] = getMousePositionImpl();
// 		return y;
// 	}

// 	MousePosition OpenGLInputPoll::getMousePositionImpl(){
// 		auto window = static_cast<GLFWwindow *>(Application::Get().GetWindow().getNativeWindow());

// 		double xpos, ypos;
// 		glfwGetCursorPos(window, &xpos, &ypos);

// 		MousePosition position = {(float)xpos, (float)ypos};
// 		return position;
// 	}
// };
#include <Engine3D/Engine3DPrecompiledHeader.h>
#include <Engine3D/Event/InputPoll.h>


namespace Engine3D{
    InputPoll* InputPoll::instance = new InputPoll();

    bool InputPoll::IsKeyPressed(KeyCode keycode){
        auto window = static_cast<GLFWwindow *>(Application::Get().GetNativeWindow());
		// auto window = static_cast<GLFWwindow *>(Application::Get().GetWindow().getNativeWindow());

        auto state = glfwGetKey(window, static_cast<int32_t>(keycode));
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool InputPoll::IsMousePressed(MouseCode mouseCode){
        auto window = static_cast<GLFWwindow *>(Application::Get().GetNativeWindow());
        auto state = glfwGetMouseButton(window, static_cast<int32_t>(mouseCode));
        return state == GLFW_PRESS;
    }

    glm::vec2 InputPoll::GetMousePos(){
        auto window = static_cast<GLFWwindow *>(Application::Get().GetNativeWindow());
        double xPos, yPos;
        glfwGetCursorPos(window, &xPos, &yPos);

        return {xPos, yPos};
    }

    float InputPoll::GetMouseX(){ return GetMousePos().x; }

    float InputPoll::GetMouseY(){ return GetMousePos().y; }
};
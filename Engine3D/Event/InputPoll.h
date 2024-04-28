#pragma once
#include <Engine3D/Core/core.h>
#include <Engine3D/Events/KeyCodes.h>
#include <Engine3D/Events/MouseButtonCodes.h>

namespace Engine3D{
	struct MousePosition{
		float xpos = 0.0f;
		float ypos = 0.0f;
	};

	class ENGINE_API InputPoll {
	public:
		inline static bool isKeyPressed(KeyCode keycode){
			return _instance->isKeyPressedImpl(keycode);
		}
		
		inline static bool isMouseButtonPressed(Mouse button){
			return _instance->isMouseButtonPressedImpl(button);
		}

		inline static MousePosition getMousePosition(){
			return _instance->getMousePositionImpl();
		}
		
		inline static float getMouseX(){
			return _instance->getMouseXImpl();
		}

		inline static float getMouseY(){
			return _instance->getMouseYImpl();
		}

	protected:
		virtual bool isKeyPressedImpl(Key keycode) = 0;
		virtual bool isMouseButtonPressedImpl(Mouse button) = 0;
		virtual MousePosition getMousePositionImpl() = 0;
		
		virtual float getMouseXImpl() = 0;
		virtual float getMouseYImpl() = 0;

	private:
		static InputPoll* _instance;
	};
};

#pragma once

// RENDER_ stands for RendererEngine
// Since there is no actual name for this GameEngine, we will just call it that
// If we do want to change it then just replace "RENDER_" withh whatever abbreviated name of your choosing

// from glfw3.h
// #define RENDER_MOUSE_BUTTON_1         0
// #define RENDER_MOUSE_BUTTON_2         1
// #define RENDER_MOUSE_BUTTON_3         2
// #define RENDER_MOUSE_BUTTON_4         3
// #define RENDER_MOUSE_BUTTON_5         4
// #define RENDER_MOUSE_BUTTON_6         5
// #define RENDER_MOUSE_BUTTON_7         6
// #define RENDER_MOUSE_BUTTON_8         7
// #define RENDER_MOUSE_BUTTON_LAST      RENDER_MOUSE_BUTTON_8
// #define RENDER_MOUSE_BUTTON_LEFT      RENDER_MOUSE_BUTTON_1
// #define RENDER_MOUSE_BUTTON_RIGHT     RENDER_MOUSE_BUTTON_2
// #define RENDER_MOUSE_BUTTON_MIDDLE    RENDER_MOUSE_BUTTON_3
#pragma once

namespace RendererEngine{
	typedef enum class MouseCode : uint16_t{
		// From glfw3.h
		Button0                = 0,
		Button1                = 1,
		Button2                = 2,
		Button3                = 3,
		Button4                = 4,
		Button5                = 5,
		Button6                = 6,
		Button7                = 7,

		ButtonLast             = Button7,
		ButtonLeft             = Button0,
		ButtonRight            = Button1,
		ButtonMiddle           = Button2
	} Mouse;
	
	inline std::ostream& operator<<(std::ostream& os, MouseCode mouseCode)
	{
		os << static_cast<int32_t>(mouseCode);
		return os;
	}
}

#define RENDER_MOUSE_BUTTON_0      ::RendererEngine::Mouse::Button0
#define RENDER_MOUSE_BUTTON_1      ::RendererEngine::Mouse::Button1
#define RENDER_MOUSE_BUTTON_2      ::RendererEngine::Mouse::Button2
#define RENDER_MOUSE_BUTTON_3      ::RendererEngine::Mouse::Button3
#define RENDER_MOUSE_BUTTON_4      ::RendererEngine::Mouse::Button4
#define RENDER_MOUSE_BUTTON_5      ::RendererEngine::Mouse::Button5
#define RENDER_MOUSE_BUTTON_6      ::RendererEngine::Mouse::Button6
#define RENDER_MOUSE_BUTTON_7      ::RendererEngine::Mouse::Button7
#define RENDER_MOUSE_BUTTON_LAST   ::RendererEngine::Mouse::ButtonLast
#define RENDER_MOUSE_BUTTON_LEFT   ::RendererEngine::Mouse::ButtonLeft
#define RENDER_MOUSE_BUTTON_RIGHT  ::RendererEngine::Mouse::ButtonRight
#define RENDER_MOUSE_BUTTON_MIDDLE ::RendererEngine::Mouse::ButtonMiddle
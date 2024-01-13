#pragma once

// // REN stands for RENDERER
// // Since we are calling this GameEngine for right now, this is what we're going with

// // From glfw3.h
// /* The unknown key */
// #define RENDER_KEY_UNKNOWN            -1

// /* Printable keys */
// #define RENDER_KEY_SPACE              32
// #define RENDER_KEY_APOSTROPHE         39  /* ' */
// #define RENDER_KEY_COMMA              44  /* , */
// #define RENDER_KEY_MINUS              45  /* - */
// #define RENDER_KEY_PERIOD             46  /* . */
// #define RENDER_KEY_SLASH              47  /* / */
// #define RENDER_KEY_0                  48
// #define RENDER_KEY_1                  49
// #define RENDER_KEY_2                  50
// #define RENDER_KEY_3                  51
// #define RENDER_KEY_4                  52
// #define RENDER_KEY_5                  53
// #define RENDER_KEY_6                  54
// #define RENDER_KEY_7                  55
// #define RENDER_KEY_8                  56
// #define RENDER_KEY_9                  57
// #define RENDER_KEY_SEMICOLON          59  /* ; */
// #define RENDER_KEY_EQUAL              61  /* = */
// #define RENDER_KEY_A                  65
// #define RENDER_KEY_B                  66
// #define RENDER_KEY_C                  67
// #define RENDER_KEY_D                  68
// #define RENDER_KEY_E                  69
// #define RENDER_KEY_F                  70
// #define RENDER_KEY_G                  71
// #define RENDER_KEY_H                  72
// #define RENDER_KEY_I                  73
// #define RENDER_KEY_J                  74
// #define RENDER_KEY_K                  75
// #define RENDER_KEY_L                  76
// #define RENDER_KEY_M                  77
// #define RENDER_KEY_N                  78
// #define RENDER_KEY_O                  79
// #define RENDER_KEY_P                  80
// #define RENDER_KEY_Q                  81
// #define RENDER_KEY_R                  82
// #define RENDER_KEY_S                  83
// #define RENDER_KEY_T                  84
// #define RENDER_KEY_U                  85
// #define RENDER_KEY_V                  86
// #define RENDER_KEY_W                  87
// #define RENDER_KEY_X                  88
// #define RENDER_KEY_Y                  89
// #define RENDER_KEY_Z                  90
// #define RENDER_KEY_LEFT_BRACKET       91  /* [ */
// #define RENDER_KEY_BACKSLASH          92  /* \ */
// #define RENDER_KEY_RIGHT_BRACKET      93  /* ] */
// #define RENDER_KEY_GRAVE_ACCENT       96  /* ` */
// #define RENDER_KEY_WORLD_1            161 /* non-US #1 */
// #define RENDER_KEY_WORLD_2            162 /* non-US #2 */

// /* Function keys */
// #define RENDER_KEY_ESCAPE             256
// #define RENDER_KEY_ENTER              257
// #define RENDER_KEY_TAB                258
// #define RENDER_KEY_BACKSPACE          259
// #define RENDER_KEY_INSERT             260
// #define RENDER_KEY_DELETE             261
// #define RENDER_KEY_RIGHT              262
// #define RENDER_KEY_LEFT               263
// #define RENDER_KEY_DOWN               264
// #define RENDER_KEY_UP                 265
// #define RENDER_KEY_PAGE_UP            266
// #define RENDER_KEY_PAGE_DOWN          267
// #define RENDER_KEY_HOME               268
// #define RENDER_KEY_END                269
// #define RENDER_KEY_CAPS_LOCK          280
// #define RENDER_KEY_SCROLL_LOCK        281
// #define RENDER_KEY_NUM_LOCK           282
// #define RENDER_KEY_PRINT_SCREEN       283
// #define RENDER_KEY_PAUSE              284
// #define RENDER_KEY_F1                 290
// #define RENDER_KEY_F2                 291
// #define RENDER_KEY_F3                 292
// #define RENDER_KEY_F4                 293
// #define RENDER_KEY_F5                 294
// #define RENDER_KEY_F6                 295
// #define RENDER_KEY_F7                 296
// #define RENDER_KEY_F8                 297
// #define RENDER_KEY_F9                 298
// #define RENDER_KEY_F10                299
// #define RENDER_KEY_F11                300
// #define RENDER_KEY_F12                301
// #define RENDER_KEY_F13                302
// #define RENDER_KEY_F14                303
// #define RENDER_KEY_F15                304
// #define RENDER_KEY_F16                305
// #define RENDER_KEY_F17                306
// #define RENDER_KEY_F18                307
// #define RENDER_KEY_F19                308
// #define RENDER_KEY_F20                309
// #define RENDER_KEY_F21                310
// #define RENDER_KEY_F22                311
// #define RENDER_KEY_F23                312
// #define RENDER_KEY_F24                313
// #define RENDER_KEY_F25                314
// #define RENDER_KEY_KP_0               320
// #define RENDER_KEY_KP_1               321
// #define RENDER_KEY_KP_2               322
// #define RENDER_KEY_KP_3               323
// #define RENDER_KEY_KP_4               324
// #define RENDER_KEY_KP_5               325
// #define RENDER_KEY_KP_6               326
// #define RENDER_KEY_KP_7               327
// #define RENDER_KEY_KP_8               328
// #define RENDER_KEY_KP_9               329
// #define RENDER_KEY_KP_DECIMAL         330
// #define RENDER_KEY_KP_DIVIDE          331
// #define RENDER_KEY_KP_MULTIPLY        332
// #define RENDER_KEY_KP_SUBTRACT        333
// #define RENDER_KEY_KP_ADD             334
// #define RENDER_KEY_KP_ENTER           335
// #define RENDER_KEY_KP_EQUAL           336
// #define RENDER_KEY_LEFT_SHIFT         340
// #define RENDER_KEY_LEFT_CONTROL       341
// #define RENDER_KEY_LEFT_ALT           342
// #define RENDER_KEY_LEFT_SUPER         343
// #define RENDER_KEY_RIGHT_SHIFT        344
// #define RENDER_KEY_RIGHT_CONTROL      345
// #define RENDER_KEY_RIGHT_ALT          346
// #define RENDER_KEY_RIGHT_SUPER        347
// #define RENDER_KEY_MENU               348
namespace RendererEngine{
	typedef enum class KeyCode : uint16_t {
		// From glfw3.h
		Space               = 32,
		Apostrophe          = 39, /* ' */
		Comma               = 44, /* , */
		Minus               = 45, /* - */
		Period              = 46, /* . */
		Slash               = 47, /* / */

		D0                  = 48, /* 0 */
		D1                  = 49, /* 1 */
		D2                  = 50, /* 2 */
		D3                  = 51, /* 3 */
		D4                  = 52, /* 4 */
		D5                  = 53, /* 5 */
		D6                  = 54, /* 6 */
		D7                  = 55, /* 7 */
		D8                  = 56, /* 8 */
		D9                  = 57, /* 9 */

		Semicolon           = 59, /* ; */
		Equal               = 61, /* = */

		A                   = 65,
		B                   = 66,
		C                   = 67,
		D                   = 68,
		E                   = 69,
		F                   = 70,
		G                   = 71,
		H                   = 72,
		I                   = 73,
		J                   = 74,
		K                   = 75,
		L                   = 76,
		M                   = 77,
		N                   = 78,
		O                   = 79,
		P                   = 80,
		Q                   = 81,
		R                   = 82,
		S                   = 83,
		T                   = 84,
		U                   = 85,
		V                   = 86,
		W                   = 87,
		X                   = 88,
		Y                   = 89,
		Z                   = 90,

		LeftBracket         = 91,  /* [ */
		Backslash           = 92,  /* \ */
		RightBracket        = 93,  /* ] */
		GraveAccent         = 96,  /* ` */

		World1              = 161, /* non-US #1 */
		World2              = 162, /* non-US #2 */

		/* Function keys */
		Escape              = 256,
		Enter               = 257,
		Tab                 = 258,
		Backspace           = 259,
		Insert              = 260,
		Delete              = 261,
		Right               = 262,
		Left                = 263,
		Down                = 264,
		Up                  = 265,
		PageUp              = 266,
		PageDown            = 267,
		Home                = 268,
		End                 = 269,
		CapsLock            = 280,
		ScrollLock          = 281,
		NumLock             = 282,
		PrintScreen         = 283,
		Pause               = 284,
		F1                  = 290,
		F2                  = 291,
		F3                  = 292,
		F4                  = 293,
		F5                  = 294,
		F6                  = 295,
		F7                  = 296,
		F8                  = 297,
		F9                  = 298,
		F10                 = 299,
		F11                 = 300,
		F12                 = 301,
		F13                 = 302,
		F14                 = 303,
		F15                 = 304,
		F16                 = 305,
		F17                 = 306,
		F18                 = 307,
		F19                 = 308,
		F20                 = 309,
		F21                 = 310,
		F22                 = 311,
		F23                 = 312,
		F24                 = 313,
		F25                 = 314,

		/* Keypad */
		KP0                 = 320,
		KP1                 = 321,
		KP2                 = 322,
		KP3                 = 323,
		KP4                 = 324,
		KP5                 = 325,
		KP6                 = 326,
		KP7                 = 327,
		KP8                 = 328,
		KP9                 = 329,
		KPDecimal           = 330,
		KPDivide            = 331,
		KPMultiply          = 332,
		KPSubtract          = 333,
		KPAdd               = 334,
		KPEnter             = 335,
		KPEqual             = 336,

		LeftShift           = 340,
		LeftControl         = 341,
		LeftAlt             = 342,
		LeftSuper           = 343,
		RightShift          = 344,
		RightControl        = 345,
		RightAlt            = 346,
		RightSuper          = 347,
		Menu                = 348
	} Key;

	inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
	{
		os << static_cast<int32_t>(keyCode);
		return os;
	}
}

// From glfw3.h
#define RENDER_KEY_SPACE           ::RendererEngine::Key::Space
#define RENDER_KEY_APOSTROPHE      ::RendererEngine::Key::Apostrophe    /* ' */
#define RENDER_KEY_COMMA           ::RendererEngine::Key::Comma         /* , */
#define RENDER_KEY_MINUS           ::RendererEngine::Key::Minus         /* - */
#define RENDER_KEY_PERIOD          ::RendererEngine::Key::Period        /* . */
#define RENDER_KEY_SLASH           ::RendererEngine::Key::Slash         /* / */
#define RENDER_KEY_0               ::RendererEngine::Key::D0
#define RENDER_KEY_1               ::RendererEngine::Key::D1
#define RENDER_KEY_2               ::RendererEngine::Key::D2
#define RENDER_KEY_3               ::RendererEngine::Key::D3
#define RENDER_KEY_4               ::RendererEngine::Key::D4
#define RENDER_KEY_5               ::RendererEngine::Key::D5
#define RENDER_KEY_6               ::RendererEngine::Key::D6
#define RENDER_KEY_7               ::RendererEngine::Key::D7
#define RENDER_KEY_8               ::RendererEngine::Key::D8
#define RENDER_KEY_9               ::RendererEngine::Key::D9
#define RENDER_KEY_SEMICOLON       ::RendererEngine::Key::Semicolon     /* ; */
#define RENDER_KEY_EQUAL           ::RendererEngine::Key::Equal         /* = */
#define RENDER_KEY_A               ::RendererEngine::Key::A
#define RENDER_KEY_B               ::RendererEngine::Key::B
#define RENDER_KEY_C               ::RendererEngine::Key::C
#define RENDER_KEY_D               ::RendererEngine::Key::D
#define RENDER_KEY_E               ::RendererEngine::Key::E
#define RENDER_KEY_F               ::RendererEngine::Key::F
#define RENDER_KEY_G               ::RendererEngine::Key::G
#define RENDER_KEY_H               ::RendererEngine::Key::H
#define RENDER_KEY_I               ::RendererEngine::Key::I
#define RENDER_KEY_J               ::RendererEngine::Key::J
#define RENDER_KEY_K               ::RendererEngine::Key::K
#define RENDER_KEY_L               ::RendererEngine::Key::L
#define RENDER_KEY_M               ::RendererEngine::Key::M
#define RENDER_KEY_N               ::RendererEngine::Key::N
#define RENDER_KEY_O               ::RendererEngine::Key::O
#define RENDER_KEY_P               ::RendererEngine::Key::P
#define RENDER_KEY_Q               ::RendererEngine::Key::Q
#define RENDER_KEY_R               ::RendererEngine::Key::R
#define RENDER_KEY_S               ::RendererEngine::Key::S
#define RENDER_KEY_T               ::RendererEngine::Key::T
#define RENDER_KEY_U               ::RendererEngine::Key::U
#define RENDER_KEY_V               ::RendererEngine::Key::V
#define RENDER_KEY_W               ::RendererEngine::Key::W
#define RENDER_KEY_X               ::RendererEngine::Key::X
#define RENDER_KEY_Y               ::RendererEngine::Key::Y
#define RENDER_KEY_Z               ::RendererEngine::Key::Z
#define RENDER_KEY_LEFT_BRACKET    ::RendererEngine::Key::LeftBracket   /* [ */
#define RENDER_KEY_BACKSLASH       ::RendererEngine::Key::Backslash     /* \ */
#define RENDER_KEY_RIGHT_BRACKET   ::RendererEngine::Key::RightBracket  /* ] */
#define RENDER_KEY_GRAVE_ACCENT    ::RendererEngine::Key::GraveAccent   /* ` */
#define RENDER_KEY_WORLD_1         ::RendererEngine::Key::World1        /* non-US #1 */
#define RENDER_KEY_WORLD_2         ::RendererEngine::Key::World2        /* non-US #2 */

/* Function keys */
#define RENDER_KEY_ESCAPE          ::RendererEngine::Key::Escape
#define RENDER_KEY_ENTER           ::RendererEngine::Key::Enter
#define RENDER_KEY_TAB             ::RendererEngine::Key::Tab
#define RENDER_KEY_BACKSPACE       ::RendererEngine::Key::Backspace
#define RENDER_KEY_INSERT          ::RendererEngine::Key::Insert
#define RENDER_KEY_DELETE          ::RendererEngine::Key::Delete
#define RENDER_KEY_RIGHT           ::RendererEngine::Key::Right
#define RENDER_KEY_LEFT            ::RendererEngine::Key::Left
#define RENDER_KEY_DOWN            ::RendererEngine::Key::Down
#define RENDER_KEY_UP              ::RendererEngine::Key::Up
#define RENDER_KEY_PAGE_UP         ::RendererEngine::Key::PageUp
#define RENDER_KEY_PAGE_DOWN       ::RendererEngine::Key::PageDown
#define RENDER_KEY_HOME            ::RendererEngine::Key::Home
#define RENDER_KEY_END             ::RendererEngine::Key::End
#define RENDER_KEY_CAPS_LOCK       ::RendererEngine::Key::CapsLock
#define RENDER_KEY_SCROLL_LOCK     ::RendererEngine::Key::ScrollLock
#define RENDER_KEY_NUM_LOCK        ::RendererEngine::Key::NumLock
#define RENDER_KEY_PRINT_SCREEN    ::RendererEngine::Key::PrintScreen
#define RENDER_KEY_PAUSE           ::RendererEngine::Key::Pause
#define RENDER_KEY_F1              ::RendererEngine::Key::F1
#define RENDER_KEY_F2              ::RendererEngine::Key::F2
#define RENDER_KEY_F3              ::RendererEngine::Key::F3
#define RENDER_KEY_F4              ::RendererEngine::Key::F4
#define RENDER_KEY_F5              ::RendererEngine::Key::F5
#define RENDER_KEY_F6              ::RendererEngine::Key::F6
#define RENDER_KEY_F7              ::RendererEngine::Key::F7
#define RENDER_KEY_F8              ::RendererEngine::Key::F8
#define RENDER_KEY_F9              ::RendererEngine::Key::F9
#define RENDER_KEY_F10             ::RendererEngine::Key::F10
#define RENDER_KEY_F11             ::RendererEngine::Key::F11
#define RENDER_KEY_F12             ::RendererEngine::Key::F12
#define RENDER_KEY_F13             ::RendererEngine::Key::F13
#define RENDER_KEY_F14             ::RendererEngine::Key::F14
#define RENDER_KEY_F15             ::RendererEngine::Key::F15
#define RENDER_KEY_F16             ::RendererEngine::Key::F16
#define RENDER_KEY_F17             ::RendererEngine::Key::F17
#define RENDER_KEY_F18             ::RendererEngine::Key::F18
#define RENDER_KEY_F19             ::RendererEngine::Key::F19
#define RENDER_KEY_F20             ::RendererEngine::Key::F20
#define RENDER_KEY_F21             ::RendererEngine::Key::F21
#define RENDER_KEY_F22             ::RendererEngine::Key::F22
#define RENDER_KEY_F23             ::RendererEngine::Key::F23
#define RENDER_KEY_F24             ::RendererEngine::Key::F24
#define RENDER_KEY_F25             ::RendererEngine::Key::F25

/* Keypad */
#define RENDER_KEY_KP_0            ::RendererEngine::Key::KP0
#define RENDER_KEY_KP_1            ::RendererEngine::Key::KP1
#define RENDER_KEY_KP_2            ::RendererEngine::Key::KP2
#define RENDER_KEY_KP_3            ::RendererEngine::Key::KP3
#define RENDER_KEY_KP_4            ::RendererEngine::Key::KP4
#define RENDER_KEY_KP_5            ::RendererEngine::Key::KP5
#define RENDER_KEY_KP_6            ::RendererEngine::Key::KP6
#define RENDER_KEY_KP_7            ::RendererEngine::Key::KP7
#define RENDER_KEY_KP_8            ::RendererEngine::Key::KP8
#define RENDER_KEY_KP_9            ::RendererEngine::Key::KP9
#define RENDER_KEY_KP_DECIMAL      ::RendererEngine::Key::KPDecimal
#define RENDER_KEY_KP_DIVIDE       ::RendererEngine::Key::KPDivide
#define RENDER_KEY_KP_MULTIPLY     ::RendererEngine::Key::KPMultiply
#define RENDER_KEY_KP_SUBTRACT     ::RendererEngine::Key::KPSubtract
#define RENDER_KEY_KP_ADD          ::RendererEngine::Key::KPAdd
#define RENDER_KEY_KP_ENTER        ::RendererEngine::Key::KPEnter
#define RENDER_KEY_KP_EQUAL        ::RendererEngine::Key::KPEqual

#define RENDER_KEY_LEFT_SHIFT      ::RendererEngine::Key::LeftShift
#define RENDER_KEY_LEFT_CONTROL    ::RendererEngine::Key::LeftControl
#define RENDER_KEY_LEFT_ALT        ::RendererEngine::Key::LeftAlt
#define RENDER_KEY_LEFT_SUPER      ::RendererEngine::Key::LeftSuper
#define RENDER_KEY_RIGHT_SHIFT     ::RendererEngine::Key::RightShift
#define RENDER_KEY_RIGHT_CONTROL   ::RendererEngine::Key::RightControl
#define RENDER_KEY_RIGHT_ALT       ::RendererEngine::Key::RightAlt
#define RENDER_KEY_RIGHT_SUPER     ::RendererEngine::Key::RightSuper
#define RENDER_KEY_MENU            ::RendererEngine::Key::Menu
// #pragma once

// #include <cstdarg>
// #include <memory>
// #include <utility>
// #include <algorithm>
// #include <functional>
// #include <sstream>

// #include <string>
// #include <vector>
// #include <unordered_map>
// #include <unordered_set>

// #include <Engine3D/Events/ApplicationEvent.h>

// #include <Engine3D/Core/EngineLogger.h>
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <cstdarg>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <sstream>

#include <array>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <thread>

// OpenGL includes
#ifndef __gl__h
#include <glad/glad.h>
#endif
#include <GLFW/glfw3.h>
#include <Engine3D/Events/ApplicationEvent.h>

#include <Engine3D/Core/EngineLogger.h>
#include <Engine3D/Renderer2D/OrthographicCameraController.h>
#include <Engine3D/Debug/Instrumentor.h>

#include <fmt/ostream.h>
#if RENDER_PLATFORM_WINDOWS
    #include <Windows.h> // include Windows.h if we are in Windows platform
#endif
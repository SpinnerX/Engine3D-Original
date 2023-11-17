#pragma once

#include <cstdarg>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <sstream>

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include <GameEngine/EngineLogger.h>

#if RENDER_PLATFORM_WINDOWS
    #include <Windows.h> // include Windows.h if we are in Windows platform
#endif
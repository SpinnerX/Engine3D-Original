#pragma once
#include <memory>
#include <GameEngine/core.h>
#include <Logger/core/Logger.h>

namespace RendererEngine{

    class RENDER_API EnginesLogger{
    public:
        EnginesLogger();
        ~EnginesLogger();

        static void Init();

        inline static std::shared_ptr<Logger::Log>& GetCoreLogger(){ return coreLogger; }
        inline static std::shared_ptr<Logger::Log>& GetClientLogger() { return clientLogger; }

    private:
        static std::shared_ptr<Logger::Log> coreLogger;
        static std::shared_ptr<Logger::Log> clientLogger;
    };
};

// #define CORE_LOG_TRACE(...) RendererEngine::EnginesLogger::GetCoreLogger()->trace(__VA_ARGS__);

// ------------ core logs ------------
template<typename... T>
void coreLogTrace(std::string fmt, T&&... args) {
    RendererEngine::EnginesLogger::GetCoreLogger()->trace(fmt, (args)...);
}

template<typename... T>
void coreLogInfo(std::string fmt, T&&... args) {
    RendererEngine::EnginesLogger::GetCoreLogger()->info(fmt, (args)...);
}

template<typename... T>
void coreLogWarn(std::string fmt, T&&... args) {
    RendererEngine::EnginesLogger::GetCoreLogger()->warn(fmt, (args)...);
}

template<typename... T>
void coreLogError(std::string fmt, T&&... args) {
    RendererEngine::EnginesLogger::GetCoreLogger()->error(fmt, (args)...);
}

template<typename... T>
void coreLogFatal(std::string fmt, T&&... args) {
    RendererEngine::EnginesLogger::GetCoreLogger()->fatal(fmt, (args)...);
}

// ------------ Client logs ------------
template<typename... T>
void clientLogTrace(std::string fmt, T&&... args) {
    RendererEngine::EnginesLogger::GetClientLogger()->trace(fmt, (args)...);
}

template<typename... T>
void clientLogInfo(std::string fmt, T&&... args) {
    RendererEngine::EnginesLogger::GetClientLogger()->info(fmt, (args)...);
}

template<typename... T>
void clientLogWarn(std::string fmt, T&&... args) {
    RendererEngine::EnginesLogger::GetClientLogger()->warn(fmt, (args)...);
}

template<typename... T>
void clientLogError(std::string fmt, T&&... args) {
    RendererEngine::EnginesLogger::GetClientLogger()->error(fmt, (args)...);
}

template<typename... T>
void clientLogFatal(std::string fmt, T&&... args) {
    RendererEngine::EnginesLogger::GetClientLogger()->fatal(fmt, (args)...);
}
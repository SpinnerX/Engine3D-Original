#pragma once
#include <memory>
#include <GameEngine/core.h>
#include <Logger/core/Logger.h>

namespace RendererEngine{

    class RENDER_API EngineLogger{
    public:
        EngineLogger();
        ~EngineLogger();

        static void Init();

        // If either coreLogger or clientLogger is nullptr
        // Then we should automatically terminate the app.
        // This is because if we continue, we will segfault due to the coreLogger/clientLogger not being initialized
        static bool isLoggerInit() {
            return (coreLogger == nullptr || clientLogger == nullptr);
        }

        inline static std::shared_ptr<Logger::Log>& GetCoreLogger(){
            if(EngineLogger::isLoggerInit()){
                Logger::fatal("EngineLogger::Init() needs to be called!\nEngineLogger::Init() returns a nullptr");
                std::terminate();
            }
            return coreLogger;
        }

        inline static std::shared_ptr<Logger::Log>& GetClientLogger() {
            if(EngineLogger::isLoggerInit()){
                Logger::fatal("EngineLogger::Init() needs to be called!\n");
                std::terminate();
            }
            
            return clientLogger;
        }

    private:
        static std::shared_ptr<Logger::Log> coreLogger;
        static std::shared_ptr<Logger::Log> clientLogger;
    };
};

// ------------ core logs ------------
template<typename... T>
void coreLogTrace(std::string fmt, T&&... args) {
    RendererEngine::EngineLogger::GetCoreLogger()->trace(fmt, (args)...);
}

template<typename... T>
void coreLogInfo(std::string fmt, T&&... args) {
    RendererEngine::EngineLogger::GetCoreLogger()->info(fmt, (args)...);
}

template<typename... T>
void coreLogWarn(std::string fmt, T&&... args) {
    RendererEngine::EngineLogger::GetCoreLogger()->warn(fmt, (args)...);
}

template<typename... T>
void coreLogError(std::string fmt, T&&... args) {
    RendererEngine::EngineLogger::GetCoreLogger()->error(fmt, (args)...);
}

template<typename... T>
void coreLogFatal(std::string fmt, T&&... args) {
    RendererEngine::EngineLogger::GetCoreLogger()->fatal(fmt, (args)...);
}

// ------------ Client logs ------------
template<typename... T>
void clientLogTrace(std::string fmt, T&&... args) {
    RendererEngine::EngineLogger::GetClientLogger()->trace(fmt, (args)...);
}

template<typename... T>
void clientLogInfo(std::string fmt, T&&... args) {
    RendererEngine::EngineLogger::GetClientLogger()->info(fmt, (args)...);
}

template<typename... T>
void clientLogWarn(std::string fmt, T&&... args) {
    RendererEngine::EngineLogger::GetClientLogger()->warn(fmt, (args)...);
}

template<typename... T>
void clientLogError(std::string fmt, T&&... args) {
    RendererEngine::EngineLogger::GetClientLogger()->error(fmt, (args)...);
}

template<typename... T>
void clientLogFatal(std::string fmt, T&&... args) {
    RendererEngine::EngineLogger::GetClientLogger()->fatal(fmt, (args)...);
}
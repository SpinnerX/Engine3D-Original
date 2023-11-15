#pragma once
#include <memory>
#include <GameEngine/core.h>
#include <Logger/core/Logger.h>
// namespace Logger{
//     class Log;
// };

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
#include <GameEngine/EngineLogger.h>

namespace RendererEngine{
    std::shared_ptr<Logger::Log> EngineLogger::coreLogger;
    std::shared_ptr<Logger::Log> EngineLogger::clientLogger;

    EngineLogger::EngineLogger(){}

    EngineLogger::~EngineLogger(){}

    void EngineLogger::Init(){
        coreLogger = std::make_shared<Logger::Log>("GameEngine");
        clientLogger = std::make_shared<Logger::Log>("APP");
    }

};
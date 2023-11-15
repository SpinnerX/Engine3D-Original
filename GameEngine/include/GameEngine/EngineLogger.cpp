#include <GameEngine/EngineLogger.h>

namespace RendererEngine{
    std::shared_ptr<Logger::Log> EnginesLogger::coreLogger;
    std::shared_ptr<Logger::Log> EnginesLogger::clientLogger;

    EnginesLogger::EnginesLogger(){}

    EnginesLogger::~EnginesLogger(){}

    void EnginesLogger::Init(){
        coreLogger = std::make_shared<Logger::Log>("GameEngine");
        clientLogger = std::make_shared<Logger::Log>("APP");
        

    }

};
#include "Application.h"
#include <GameEngine/Events/ApplicationEvent.h>
#include <GameEngine/EngineLogger.h>

namespace RendererEngine{
    Application::Application(){}

    Application::~Application(){}


    void Application::Run(){
        WindowResizeEvent e(1280, 420);
        coreLogInfo("{}\n", fmt::streamed(e));
        while(true);
    }
};
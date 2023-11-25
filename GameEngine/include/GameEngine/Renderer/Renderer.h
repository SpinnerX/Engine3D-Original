#pragma once


namespace RendererEngine{

    // Should be stored in a static state
    enum class RendererAPI{
        None = 0, // if you're running headless, or you just don't want to be running rendering because unit tests dont use rendering
        OpenGL = 1 //if we only want to run OpenGL rendering API's
    };

    class Renderer{
    public:
        inline static RendererAPI getAPI() { return _rendererAPI; }

    private:
        static RendererAPI _rendererAPI;
    };
};
// #pragma once
#ifndef CORE_H
#define CORE_H
#include <bitset>
// Essentially to support Windows/Mac/Linux systems

// if we are on the Windows OS (since windows uses dll files)
#ifdef RENDER_PLATFORM_WINDOWS
    #ifdef RENDER_BUILD_DLL
        #define RENDER_API __declspec(dllexport)
    #else
        #define RENDER_API __declspec(dllimport)
    #endif
#else // If we are on either Linux/Mac OS, since they use __attributes__
    #define RENDER_API __attribute__((visibility("default")))
#endif


// What this does is checks a specific condition
// Then it logs the message if it fails then calls __debug break (kind of like setting a breakpoint)
#ifdef RENDER_ENABLE_ASSERTS
    template<typename... T>
    void render_assert(bool x, T&&... args){
        if(!(x)){
            clientLogError("Assertion Failed: {}", std::forward(args)...);
            __debugbreak();
        }
    }

    template<typename... T>
    void render_core_assert(bool x, T&&... args){
        if(!(x)){
            coreLogError("Assertion Failed: {}", std::forward(args)...);
            __debugbreak();
        }
    }
#else
    // #define RENDER_ASSERT(x, ...)
    // #define RENDER_CORE_ASSERT(x, ...)
    template<typename... T>
    void render_assert(bool x, T&&... args){}

    template<typename... T>
    void render_core_assert(bool x, T&&... args){}
#endif

// Using a bitfield to go into multiple categories
// Hence, why we are using a bitfield.
constexpr uint64_t bit(uint64_t x){
    return (1 << x);
}
#endif
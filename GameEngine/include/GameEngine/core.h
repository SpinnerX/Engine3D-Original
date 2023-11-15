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

// Using a bitfield to go into multiple categories
// Hence, why we are using a bitfield.
constexpr uint64_t bit(uint64_t x){
    return (1 << x);
}
#endif
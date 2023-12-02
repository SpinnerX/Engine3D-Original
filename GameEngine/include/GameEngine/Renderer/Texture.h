#pragma once
#include <GameEngine/core.h>
#include <string>

namespace RendererEngine{


    /**
     * @brief 
     * 
     * @class Texture (class) - Pure virtual class representing the texture
     * @class Texture2D - Represents our actual 2D texture pure virtual class interface for different platforms to impl
     */
    class Texture{
    public:
        virtual ~Texture() = default;

        virtual uint32_t getWidth() const = 0;
        virtual uint32_t getHeight() const = 0;

        virtual void bind(uint32_t slot=0) const = 0;
    };


    class Texture2D : public Texture{
    public:
        Texture2D() = default;
        Texture2D(const std::string& filepath);
        static Ref<Texture2D> Create(const std::string& filepath);
    };
};
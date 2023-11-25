#pragma once

namespace RendererEngine{
    // Buffer.h
    // - will represent Vertex buffer and Index buffer
    // - These are our pure virtual interfaces meaning no impl
    // - No member variables, and should not take no storage, only 1 byte when we initialize because it has to
    // - Literally just a vtable of functions of thosen virtual functions that'll get dispatched to whatever kind of
    //   subclass that realizes this class.


    // Vertex Buffer (what does a vertex buffer need?)
    // - Needs a bind()
    // - 
    class VertexBuffer{
    public:
        virtual ~VertexBuffer(){}

        virtual void bind() const = 0;
        virtual void unbind() const = 0;

        static VertexBuffer* Create(float* vertices, uint32_t size);

    };

    class IndexBuffer{
    public:
        virtual ~IndexBuffer(){}
        virtual void bind() const = 0;
        virtual void unbind() const = 0;

        virtual uint32_t getCount() const = 0;

        static IndexBuffer* Create(uint32_t* vertices, uint32_t size);
    };
};
### Implementing and Integrating a Renderer (Context) API Abstraction into the Engine (not the renderer yet)


### Overview
- Implementing a renderer for the engine
- Starts to look into implementing the renderer architectures and integrating the renderer into the Engine.


### Summary References to Renderer Architecture
- Shaders, Vertex Buffers, and other primitives would be considered as part of the Rendering API
- This is because you'd generally create these rendering API's to help with the actual renderer
- Such as 2D and 3D Renderer (Forward, Deferred, etc.), Scene Graph, Sorting, Materials \   
    would be part of the renderer
- Initial difference between the two is that the renderer uses the rendering API that is platform \
    specific,

### Requirements for Renderer API and the Renderer
Renderer API (Requirements that is API/platform specific)
    - Rendering context 
    - Swap Chain
    - FrameBuffer
    - Vertex Buffer
    - Index Buffer
    - Texture
    - Shader
    - States
    - Pipelines
    - Render Passes

Renderer (API/Platform agnostic)
    - 2D and 3D Renderer
        * Forward, Deferred, etc.
    - Scene Graph
    - Sorting
    - Culling
    - Materials
    - LOD
    - Animation
    - Camera
    - VFX


###  Process when implementing a renderer 
- First thing needed when starting to create renderer is a rendering context.
    - Needing a way to create a context for the API (GLFW handles all that for us)
        ** NOTE ** In vulkan it would be difficult because of swap chain, because we'd need to \ 
                 doing things like physical devices, such as knowing to utilize the GPU's, etc.
- 

### Classes Added


### Features (Implemented in this phase)
- First things, first is implementing our RendererContext and a basic Renderer.
    - Possibly calling it a GraphicsContex.
    - Implemented a GraphicsContext that is an interface thhat will be used by the RendererContext
    - Reasons for having GraphicsContext is to allow to create different contextual interfaces \
        that may be used by other context when we are potentially rendering different things.
- Added the RendererContext into WindowsWindow.h
    - This is so we can start integrating this renderer into thhe onUpdate function
    - Allowing to swap chains/swap buffers whenever we call update
- When we call glClear(), we now want the Renderer system to sort of handle that itself, and not the client-side
    - Like when we are calling glClear() in the mainloop.

### Heirarchy Visualization
GraphicsContext (Base Interface Class) -> RendererContext(Subclass of the pure virtual interface class)
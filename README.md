## Game Engine Tutorial
Name: RendererEngine 

### NOTE: There will be a video showcasing the usage of this engine, once the renderer has fully been implemented.

## Overview
Learning about game engine development. Of how we can use different data and transform them into various \
things. 


## NOTES
Directory NOTES.review contains notes on what is learned through developing game engines. Including \
developing how the subsytems inside a game engine works. Containing more notes descripting in \
specific topics. Where each notes will be numbered on the process it takes when developing a game engine.


`__attribute__((visibility("default")))`
- Just know that this is the Mac's version of  __declspec(dllexport). \
-  Also known as GCC specific keyword to control whether it is available for linking other objects or shared libraries, \
    or whether it is hidden and only available within the physical file (obj or library) where it is defined, the \
    visibility symbols in C++ that is set to default. \
- In simplification this means that the declared function or class is visible to other translation units. \
    - Basically meaning that they can be used by other shared libraries or objects that are currently linked to the current library or object.


## Resources
`https://icolorpalette.com/color/102669` - Link for medium royal blue colors
`https://registry.khronos.org/OpenGL/specs/gl/glspec46.core.pdf` - OpenGL 4.6 fundamentals readings.

### Checklist
* Batch Renderer
* Profiling (Debugging)
* Entity Component System (ECS)
* Native Scripting
* Adding/Deleting Entities (using UI)
* Serializing/Deserializing
* Saving/Loading UI for serializer/deserializer
* Gizmo

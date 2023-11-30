### Shader Abstractions and Uniforms
- Updated Shaders class that can modify uniforms
- Abstracting away the Shader class
- Basically having one platform specific shader class, int this case being OpenGLShader
- Where we make the Shader class more a generic interface


### Overview
- Added OpenGLShader: so that we have shaders that use OpenGL's rendering API's
- Made Shader class more a generic pure virtual class, that will only be used to create platform-specific \
    shaders, essentially.
- New thing added were instead of statically modifying our shaders, we created a UI allowing for our \
    shaders to be able to be dynamically modified through the color pickup.
- Shader class is now pure virtual interface, and use OpenGLShader for any shader related things that are specific to OpenGL.
- Added UI settings to change shaders through a UI, rather then changing literaly values.
    - once again, to allow for dynamically changing shaders.
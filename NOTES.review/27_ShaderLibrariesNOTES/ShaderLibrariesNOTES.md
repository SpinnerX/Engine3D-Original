### Shader Libraries
- Basically a way for us to literally store all of our shaders inside our library
- Providing control for users to create shaders, and other common tasks that shaders are able to \
    do.
- Developing a shader library for the renderer
- Allowing the engine to initialize diagnostic shaders
- Idea is to have a Shader library in the game engine to basically allow an easier way to creating and \
    storing shaders.



### Features
** In Shader.h **
- Created ShaderLibrary class
    - Allowed for us to store, load, and access shaders that are being processed in ShaderLibrary class.
    - This allows users to have a better time creating shaders, or even loading shaders from .glsl files
    - This class is able to parse filepaths, and simply utilize the name of the file as the id, and the actual \
        shader as the value in the unordered_map.
    ** Example of that **
    Instead of doing this (in the constructor or other functions, for example)
    auto shader.reset(Shader::Create("assets/shaders/Texture.glsl));

    and doing something like this in that same function:
    shader->bind()

     ** New way of doing that **
    auto shader2 = Shader::Create("assets/shaders/Texture.glsl); // Assuming this is in another function like initialization, or something like that

    // And assuming this needs to be called in the onUpdate function
    // we can do this instead (which gives us a way to actually access our shaders and not let that be limited by the scope of these calls.)
    RendererEngine::Shader::submit(shader2.get("Texture"), ...);

** Another thing to add potentially **
- Instead of just creating an object, initially we would want this to be only one instance to handle storing, loading, and accessing these shaders
- Hence probably wanting this to be static, just so we have a way of accesing these shaders throughout our engine.
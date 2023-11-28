### Rendering API Abstractions


### Introduction to Rendering API Abstractions (in the context of Compile-time and Runtime)
1.) Compile and Run-time code
    - Biggest choice to note that'll need to be decided is if you are going to have to support either \
        during compile or runtime.
    -  If you want to do compile-time, then you'll need to select a rendering API for that (as an example, DirectX).
        - What exactly happens is you can basically choose to compile with Direct X.
        - Though if you decide to choose opengl, then all the files that are opengl specific into your final
    ** practical example **
    - Essentially each kind or rendering API files that can break down into primitives.
        - Like having a vertex buffer, index buffer, textures class, shader class, etc.
        - Then essentially having an OpenGL shader class, a DirectX shader class where one of these classes \
            would be compiled.
        - The ones that get compiled would differentiate depending on the configuration settings
        - Another thing that is possible is also having #ifndef's that check to see if for example, "DirectX" is defined then \
            to run the DirectX shader class or something like that.
        - Then use that selection to compile specific chunks of code, where if that API is defined
            Example: ifndef opengl is defined, compile and run opengl code. Ifndef DirectX is defined then run DirectX code.
2.) Disadvantages of Compilation selection code
    - Disadvantages to having that compile time selection is that the codebase is going to require multiple physical builds.
    - Meaning that recompiling is something you do not want to consistently be doing during compile-time essentially for everytime \
        at compile-time are trying to select which rendering API to use, whether it is DirectX, or using OpenGL natively.
3.) Potential benefits of doing things this way
    - Primary benefits of doing it this way is performance
    - Because you know what API you are going to be using and doing that through compile-time.
        - Where the Game Engine in runtime does not have to make this decision since that decision has already been done in \
            compile time.
4.) Main components
    4.1.) Vertex Array
    4.2.) Vertex Buffer
    4.3.) Index Buffer

### Features
- Implemented Buffer.h that contain VertexBuffer and IndexBuffer interfaces
    - These interfaces will be used by other rendering API's and allowing the option for users to use \
        different rendering API's, such as OpenGL, or event DirectX.
- Implemented OpenGLVertexBuffer and OpenGLIndexBuffer that are implementations specific to the OpenGL rendering API's
- Then integrating that and using that in our Application class.
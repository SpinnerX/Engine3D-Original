### Shader Asset Files
- Idea is to, instead of using strings we use .glsl files
- Reading shaders from files instead of strings to make code cleaner and more concise.
- Splitting vertex and fragment src's under one file, then parsing that using std::ifstream \
    for now.


### Features (Added, and Modified)
- Added assets/shaders/texture.glsl
- Modified OpenGLShader to read from filepath
- Refactored and instead of just taking shaders strings, we added the ability to load in files
    - Such as parsing .glsl files
- OpenGLShader was modified to add preProcess, compile functions that use an unordered map to load and parse \
    in files.
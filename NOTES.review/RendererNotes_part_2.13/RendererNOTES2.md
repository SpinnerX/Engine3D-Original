### Continuing in Implementing the actual Renderer

### Overview
1.) Now after implementing theh RendererContext
    - We are going to implement the actual Renderer
    - This renderer is what will be one of the Core features of the engine
    - Renderer class is needed to actually handle the glClear Color, issuing rendering commands,
        rendering states.
    - Also rendering a triangle in this phase, for testing that the renderers rendering graphics correclty.
2.) For the renderer
    - These are the four things that we absolutely need for the renderer
        - Vertex Array
        - Vertex Buffer
        - Index Buffer
        - Shader
    - There isn't that much code to write in the first three, as there is more to write for Shaders \
        in the current phase we're in right now.
    The first three is essentially what is needed to get a simple triangle to render on the screen.
3.) Overview of use of Projection Matrices
Projection Matrix Overview
    - These act as 3 component coordinates in space
    - By default if you do not havce a projection matrix (or basically transforming your vertices by anything)
    - Only thhe default clip space that OpeGL handles (which is basically negative 1 to 1 in every axis)
    About Projection Matrices
    - Vertices that may contain values known are 200 or something like that would essentially use a projection matrix.
    - Because could convert values from 1 to -1
4.) New parameters to look out for
    - When we call glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer)
        - index of vertices
        - size in bytes of vertices
        - stride is the amount of bytes between different vertices, here is a sample example
        ** Example**
            - using glVertexAttribPointer function
            float vertices = {
                -0.5f, -0.5f, 0.0f,
                0.5f, -0.5f, 0.f,
                0.0f, 0.5f, 0.0f
            };
            glVertexAttribPointer(0, 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr)



### Features
- Renderer Class
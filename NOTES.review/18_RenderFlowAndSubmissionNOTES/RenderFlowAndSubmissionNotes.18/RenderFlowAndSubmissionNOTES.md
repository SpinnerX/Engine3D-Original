### Render Flow and Submission



### Overview
1.) Overview of the Draw Call
    - Simply to draw something to the screen
    - Giving it a commands, the data, necessary shaders to now being able to draw \
        to the screen.
    - Will actually run the shader, pixel fragment shader to the screen.
    ** Example **
        - Actual draw call is glDrawElements
    - Needed in order to render data properly
2.) Need a renderer. Well? What does a renderer do, exactly?
    ** Consider the following **
        - When we render a triangle, what is needed to render a triangle
        - Lets think of this as a piece of geometry
        - Such as rendering a cube. What components are needed to render a cube?
            - Need a vertex array, vertex buffer, index buffer, and shader.
            - If in a 3D world... where are we in relation to the cube?
            - How are we looking (viewing) at the cube?
            - A camera system
                - In which a camera system uses a projection matrix and a view matrix.
            - Need an actual located, needing the whole transformation matrix of the cube as that is important.
            - Need to know surface materal. (What is the cube like, such as material texture)
            - Need to know environment
                - Such as sunlight (or indirectional lighting) that comes from somewhere(src), what does the world look like
                    such as an environment map. (Like a radiance map)
                - Important for image-based lighting
        - These things described will eventually start to seperate into two different things
            - Stuff concerned with the environment, and stuff that is concerned with the actual object we are rendering
        
        ** Environment, what would that be? **
            - Lighting environment, are there point lights, big directional map.
            - Or other kinds of environemnts needed for any sort of reflections.

        ** Camera **
            - Where are we looking, which can be based off the environment.
            - You can differentiate that way in the case that you either want to render two cubes, or either \
                rendering a whole scene of objects.
            - Should you need to update each object in the environment, nope. You would just change the camera view, light setup, no that either.
                - You look at the scene from one camera to all the objects.
                - Where all objects are going to be rendered with that same set of parameters
                - So, renderer knows which object belongs to that actual scene
        - That is what we need to do to tell our renderer to begin a scene
            - Possibly a command that is basically like "Renderer Begin Scene" where it needs to know about the environment and the camera.
            - Or if you want to render 3 cubes, or got a level, walls, characters.
                - What is needed is what materials those objects are using
                - How do I render those materials, and secondly is the transformation of the object (as in where in the world is it)

3.) Process for the Renderer
    - Telling the Renderer that you're beginning a scene
    - After that is when you start supplying all the renderer stuff.
        - Camera, the environment
    - Then render all our meshes, where each mesh that we are going to render is going to be at a different transform (transformation matrix) \
        that'll make it's way to the shader.
    - Which where all our meshes go to, eventually
    - Then we finally end the scene, signaling the scene is over.
    NOTE: Though thhese stuff do not render immediately, instead it just gets submitted into the renderer-like command queue \
          essentially.
    - So, we try to render command out of it and we submit that
        - Essentially taking the time to the renderer queue. Which could be evaluated through a multithreaded renderer queue.
    - Creating a command queue of commands that the renderer has to fullfill thhen we submit scenes to the renderer queue.
    - Once the whole scene has been submitted, only then we render it.


### Features
- Created RendererAPI (a pure virtual interface class)
- Implemented Renderer
    - Contains beginScene(), endScene(), and submit()

- Pseudo-code idea of we want the code to look like
    RendererCommand::SetClearColor();
    RendererCommand::Clear();

    The goal for adding in the Renderer command calls on how we call these functions
    Renderer::BeginScene(); // Potentially Scene Settings
    _squareVertexArrays->bind();
    Renderer::Submit(_squareVA); // Submitting our meshes (or geo meshes)
    _shader->bind();
    Renderer::Submit(_vertexArray); // Submitting our meshes (or geo meshes)
    Renderer:EndScene()

    At some point we flush the renderer
    Renderer::Flush();


** Process **
    RendererAPI -> RendererCommand -> Renderer 
### Batch Rendering
* In the context of designing, implementing and working to integrating batch rendering into the engine
* Such as what, how, and why batch rendering is needed. 


### NOTES on the use cases of batch rendering and why and how it is used!
* Instead of handling draw quads manually, like per say wanting to draw hundreds and thousands of draw quads
* Batch rendering allows us to do this and not having to  manually bind bunches of quad vertex arrays
* Converting the 2D renderer to utilizing batch rendering.

### Purpose
* The engine's API needs to be easier
* When users are making API calls for the engine
* Being able to simply allow users to want to draw a specific object and things like that.



### Context
* Continue in using Renderer2D::beginScene() and Renderer2D::endScene() to attempt of batch rendering everything together with one draw calls
    * Example, is if your scene is large
        * Large as in, if you have over ten thousands quads
        * Then you'd want to divide that into multiple draw calls.
* Idea behind Batch Rendering
    * Is when you begin a scene, essentially will want to create one batch
        * Attempting to render everything into one draw call.
    * However, in that begin scene if exceeding that limit of per say 10,000 quads
        * Then it'll simply flush everything it's got and then start again.
        * As in starting a new batch. (In other words, starting a new draw call)
        * Lets say the max is 10, 000 and instead we are drawing 22,000 draw calls
        * Then it would essentially come out to three draw calls.



### Features
* Updated VertexBuffers to take in only a size of VertexBuffers
* Updated RendererCommand to take in a indexCount in drawIndexed function.
* Created struct for quad vertex containing position, color, texture coordinates
* Updated Renderer2DData to contain the quadVertex base and pointer.
    * Where the pointer monitors the Vertex buffer when we draw in our batch renderer.
* Updated DrawQuad function to draw multiple rendering objects instead of considering each object with a single draw quad instead.

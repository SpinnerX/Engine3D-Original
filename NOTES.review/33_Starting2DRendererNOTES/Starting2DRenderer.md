### Starting to Think about before or current time at building a 2D renderer



### Things to consider (that can be considered before or at the time of planning to implement a 2D renderer)
*  So when trying to develop a 2D renderer, there are things that you can do way before building the 2D renderer
    * Such as profiling and memory tracking

* When developing an engine, your gonna want engine tools that do specific things, like profiling.
    * This way is because if you eventually want to support other OS's like Windows, Mac, Linux, your gonna want \
        there to be engine tools to help the engines memory usage.
    * Such as using these engine tools to look at the overhead of the engine itself.
    * An idea would be looking into how much memory the Game Engine usage is, in the actual Game Engine client space. (NOTE)
    * It is important because it can also be graphed over time.
    * Which adding those things are quite important.
    * How that can work, is literally by taking those things into your own hands.  (Especially in DEBUG mode)
    * In the future to also make smart decisions on knowing where the memory comes from. (So your not hitting the HEAP all the time)

### Future things to consider
* Custom Memory Allocations
* Custom Metrics and Tracking
* Profiling
    * What I mean, is the Game Engine will have it's own customized profiling

* Timing Mechanism
    * Basically being able to track how much time has been spent inside that function, then to visualize that data somehow
    * Can be added in the 2D renderer when you start developing it.

### Idea
1.) First Develop the renderer
    - Meaning that develop a more naive 2D renderer
    - Such as that it'll just work

2.) Then second, add profiling
    - Meaning that once it has a basic functionality, and it works
    - Then you can add in the profiling, as you build it.

### Actual 2D Renderer
* In general renderers should be static.
    * Question is, why are renderers static
        - Renderers do not have to be static.
        - Concept of static, objects, and instantiation is simply just a language construct
        - What normally matters in the end is how we are transferring data, and doing those operations efficiently
        - Because if you look at the root level of OOP, it essentially is a class that is static with a block of data.
        - By making this static, you simply are telling the compiler that you won't have a seperate block of data for each class
            - As in each instance of that class (in this case the 2D renderer), that you need to point to every time

* Since OpenGL is arbitrary gloabl, and there really is no instance of OpenGL inherently.
    * Hence, why it makes sense to have a static renderer
    * Because the renderer is sequential
        * Since there are no such thing where you start one scene with one renderer, and another scene with another renderer as that'd be weird.
        * Where everything is done sequentially from beginning the scene setting up your primitives, and ending that scene.
        * Where this could be anywhere in your codebase, hence this is what the flow of the renderer would look like.
    * Basically Dumb it down first, and then start thinking of how you would do specific things.
    * Simple before complicating it

### Features Added 2D Renderer
* Added 2D Renderer class
* Removed some code and add begin(), end(), and drawQuad() into 2D renderer
* Added Renderer2DStorage to simply act as a way to store different vertex attributes, in this case only it stores two variables
    * But more will be added


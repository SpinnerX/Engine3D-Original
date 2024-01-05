### 2D Renderer Shaders
* Require a complete sort of state switch
* Such as what if we were to need multiple Shaders
    * Simply by binding and the draw call
    * Where you'll want to switch to multiple shaders
    * Essentially what you can do to mitigate that is by doing:
        - Putting them in a command buffer, where you do drop color -> draw call -> drop color
        - Then what happens with that information, like if you wanted to draw fifty colors and quads with textures
        - Then you would basically put them into two groups
        - Putting them into two groups meaning you'd, bind your shader then doing all the quads, and then you bind your texture shaders \
            then you do all of the textured quads
    * Which essentially is fine, but really you might not even need two shaders for those
* Hence, what we are going to be adding is implementing a shader that can do both of those.
    * Instead of creating two shaders, you have one shader that can manager both.

### Context as to how we can make this happens
* 

### Features


### Textures


### Overview
- Looking into textures in the context of game engines
- Understanding them in much more details

** Textures can be much more then that **
- Which essentially is we are taking our buffer in memory, then storing it into our GPU, in our vram
- Where we can access in our shader, fragment, or even vertex shaders.
- Essentially is just data in memory that we are able to upload too.
- Its just like how our vertex buffer, are not just for storing positions, but really being able to store \
    other kinds of data that you give it.
    - Where textures are the same exact concept in reference to that.
- PBR (physic based rendering) is just a defined, and we look for that value to rendering a specific shader.


### Features
- Things that will be added is the idea, that we wan't to load in an image file from our computer \
- Then to render that image file, essentially onto a quad inside the engine.
- Though there are quite a bit of compoenents to this


### Components
1. Need to work on the geometry
    - What is needed to display at texture on the screen, or what data is needed in the geometry.
    - Specifically needing texture coordinates.
2. Modify Vertex Buffer to include texture coordinates for our objects
3. Modify the Shader class, to being able to take in sample 2D which are 2D texture slots
4. Creating texture class to loading image and storing into the GPU
    - Then get renderer ID from that, so we can just bind that ID at runtime
    - Using out rendering API



### Actual Operations and things when developing the textures portion of the engine
- When rendering a texture, your going to need to render that on some kind of geometry
- Which is the vertex buffer is what will be used.


### Some side notes that are important when validating textures visualizations
- When validating if your textures being rendered correctly, see and check to see what is being rendered correctly
- As in looking at which texture coordinates are being rendered, and understanding where are things being rendered \
    that shouldn't be rendered.



### Features (to be added when textures grow massively)
- Added Textures class (represents our texture data)
- Added Texture2D class (represents our actual textures used for rendering 2D textures)

** About texture2D **
- this may change later as it textures grow more massively
    - Being able to do more later on.
    - Such as creating Textures from memory
    - May want to create a solid texture
    - Or even a texture factory, that can create grid gradients or solid colors
    - Since they can be useful to test out
    - Even possible having an error texture that the engine could generate \
        in the cases that the texture does not load properly
    - So, in case of crashing or texture turning black, we can give the object an error \
        texture instead


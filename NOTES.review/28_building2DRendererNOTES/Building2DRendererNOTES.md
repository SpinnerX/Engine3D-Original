### Building a 2D renderer (Essentially the architecture of building a 2D renderer)
- Keeping Renderer indicating that, it'll be used for 2D rendering
- Whereas for 2D-related rendering, Renderer2D will be used to handle lots of the 2D rendering, essentially.
- We may want to have lot of 2D images, or lots of quads on the screen at once, which is done by a process called \
    batching.
    - If we are trying to render lots of 2D quads, by doing it manually that'll decrease the frame rate.
    - Where it would be better to batch those together under one whole geometry
    - All of the properties that will need to render things like quads, all that data would go into a vertex data.
    - Into a big giant vertex buffer, every frame you are updating that vertex buffer with required data.
    - So, instead of 10, 0000 Quads, it would be 10,000 draw calls.
- Which is why we need a batch renderer

1.)  Batch Rendering
    - When you start involving textures into a batch renderer
    - You quickly discover that if you hahve something like an RPG where its a 2D top down game
    - You starting thinking of textures involved within the tile map such as water, game objects, and other things in the world.
    - It is considered rare to have something like 100k sprites, and 10, 000 textures
        - Which may not actually happen, instead what would happen is that
        - 
    - The renderer will need to handle
2.) Texture Atlas System
    - A way of storing things like spritesheets, into a specific range of resolution
3.) Once we talk about textures atlas systems next thing is talking about animations.
    - Meaning animated sprites
    - Such as character movements, waters or environment movements.
    ** Example **
        - Another thing when looking at animations, is we may want spritesheets
        - Example likee using a 32x32, where we have our players textures or texture atlas, ready to go
        - Binding that texture onto the GPU
        - Where all those textures are under one frame.
        CONSIDER THE FOLLOWING: Considering what if there are resolution differences
            - Meaning that what if the size of the spritesheet is 1024x724.
        - To consider the following above with resolution differences
            - We will need a custom format that basically encodes frames would do
            NOTE: Essentially what a video encoder would do.
            - Where you will have your key frame, then the next frame is a bunch of deltas.
            - So, when all the pixels change. That's what you record for when you decide what \
                frame #1 looks like.
                - Where you go to your nearest key frame that would be back in time.
                - Frame #0, in this case and to apply those deltas through that frame
4.) UI
- Now for UI, what do we need?
- For UI, we would need a layout system.
- Layout system, can be quite complex
    - Because on a screen you may have quite a UI layout, that may have different screens
    - Or other things like main menu, resizing the window making it smaller or larger
        while still maintaining a padding system, or alignment
    - This can be done with a good layout system, especially one that can support different resolutions.
- Being able to load fonts
- Getting characters that are used dynamically into sprite sheets.
    - Figuring the best way to pack those rectangles.
- Saving on texture space, since there potentially lots of rectangles that are going to be rendered
    - So, looking into some kind of rectangle packing algorithms.

5.) Particle system
- Particle systems would also be important to look into implementing
- Along with HDR as well.
- Then adding bloom, with post effects.
- Post effects being that if the player was to be at a main menu, then you'd typically blur out \
    the background. So, users can focus on actually interacting with the main menu.
- Since this is taking a look into a 2D renderer, we do not need to focus on dynamic lighting.

** List Features (Components) we want in the 2D renderer  (Ideas) **
- Batch Renderer (Drawing 100k at 60 fps w/textures)
    - 

### Features (Things implemented or to be implemented)
- Eventually wanting the Renderer2D api to look like
** Example Pseudocode **
- Example of how we'd probably use this API
- Where Renderer2D::BeginScene(cam) would be use to start the scene
- Renderer2D::DrawQuad(pos, s, c, t) would be use to draw things like a rectangle, or something like that

RendererEngine::Renderer2D::BeginScene(_camera);
RendererEngine::Renderer2D::DrawQuad();
RendererEngine::Renderer2D::DrawCircle(); // fill in circle

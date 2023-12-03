### Adding support of Blending into our textures

### Overview
- Needing to handle blending so we can handle textures that may/may not contain alpha \
    in the RGB channels.
- What is to be expected when modifying for handling blending with textures?
    - Expected that to have a texture (1) and another texture (2) overlapping the first texture.
- Looked in how we can use alpha
    - Essentially how we can mix colors and transparency using alpha pixels
    - And how they should be rendered on the checkerboard.

** Looking as to how the engine will handle blending **
- Looking how we should initialize our renderer




### Features (Things added and modified during this phase)
- Called Init() in Renderer -> RendererCommand -> RendererAPI -> OpenGLRendererAPI
- Created Init() in RendererAPI to tell OpenGL to enable blending
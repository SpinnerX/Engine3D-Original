### Layes

### Overview
- Going over layers and how they work in game engine development.

### Understanding how layers work in game engine development
- Layers determine what order things are drawn in
- They do not just applicable to graphics, but are applicable to events \
    or updating logic
- Layer being an abstract topic, which is a section of your application that render certain things \
    and that receives events.

Analogy (Example)
- Like lets say we have a 3D game world making a 3D game, or something like that
- The 3D world sits on one layer, and all of the 3D rendering gets done on this layer, which \
    acts as our game layer. Where any events that occur as well, are sent to this layer.
- This layer is like our root.
- Potentially having a debug layer or something like that, like game debug layer.
    - May contain some kind of debugging regions, or queueing messages, or any debugging graphics is on this layer.
- Or a UI layer which is kinda like a 2D orgographical projection, which is another way \
    that layers tie in and usually have one kind of projection.

## Features

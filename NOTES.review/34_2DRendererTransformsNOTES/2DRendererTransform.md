### Transforms in 2D Renderer
* Looking into the transforms of triangles
* Since the quad currently being rendered in the current phase is in a fixed position, its basically \
    wherever the data inside that vertex buffer is where it gets rendered.
* For the drawQuad we want to be able to set the position and size, hence the name "Transform" triangles.


### Transforms
* Important for game engines, game development, tracking positions for anything
* Transform are normally a combination of TRS (which means Translation, Rotation, Scale)


### How we are going to do this
* setting up a matrix we send into our shader via uniform per draw call.
* Hence, that is going to be determining the transform our rectangle.
* However, we probably shouldn't take in the entire/whole matrices as a transform
* Normally when your drawing quads, like currently. You'll have a very simple API where it might specify a two component vector
    * two floats determining the size, and two floats determining the position
    * Where rotation might be considered in the future (since its not difficult, probably do not give or take lol)
* Fixing the shader API
* Adding transform into 2D renderer. For setting size, and position individually

### Features
* Added transforms in Sandbox2D
* Applied Transforms TRS (Translate * Rotation * Scale), but only applied Translate and Scale (Hence, T * S)
    * Though you can just do (T * R * S), if you want 


### Further Context
* Adding more context as to the importance of transforms after implementing it
* Transforms allow you when everytime you draw quad, the shapes before were simply just in fixed positions and size
* Transforms allow the shapes to no longer be a fixed position, size, and rotation.
* Hence, the importance of it. (Basically a way to allow different objects be in different locations, sizes, and rotations)

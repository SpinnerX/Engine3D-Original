### Learning about Viewports with Scenes
* Creating frame buffers allow for the scene that we are rendering to be sent to a specific frame buffer
* Which means that frame buffers allow you to change targets of where you want to render your shaders or textures.

### Viewports
* Viewports allow you to modify your dimensions of the window, and viewports help adjust the way you resize your window.
* Other words they allow you to change the way your window application is modified.


### Features Added
* Adding a resize as part of the Frame Buffer
    * Effectively allowing us to recreate a frame buffer everytime the user resizes the window.
    * This allows to modify the frame buffer the completely be full screen whenever the window itself is extended.
    * Also added glViewPort(0, 0, specs.w, specs.h);
    * Where this allows the frame to be filled whenever resized, making the scene the same regardless of the size the window is changed too.

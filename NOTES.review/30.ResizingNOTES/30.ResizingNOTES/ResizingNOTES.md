### Resizing Notes
- Utilizing glViewPort to basically handle different types of views
- Such as if you were to have different perspectives
- Different from different cameras that are composite in a frame.
- These are ways of how view ports are set.


### Frame Buffers
- Have to consider is that not all frame buffers arent the size of your window
- If you were to render a destination or intermediate scene, then they would be 1 to 1 for your actual rendering areea and your actual setting frame buffer to be.
- Considering if you were rendering a frame buffer, or shadowing map or rendering pass for bluring.
    - These are things that you shouldn't need to be tied width and height as your screen. (But good to know)
- Though these are still good to know
    - As an example, if you are keeping one of these buffers at exactly 50% over the resolution of full frame buffer
    - Then, you will want to know if your window changed (even though they are not tied to your width and height of your frame)
- Notifying those frame buffers if there's been a change in actual screen resolution, where then we can resize it and changing that frame buffer

Typically having a frame buffer poll
    - Used for storing a collection of frame buffers, where in a way you can recycle them as well if you really need to
    - Ultimately the application will know about all frame buffers, and iterate over and tell them the window has been resized.
    - So that if you were to have a frame buffer that focuses on that fills the screen, then \
        in that case it could resize it's textures, and recreate itself, essentially.

Camera
- What happens when resizing the window? There are two options.
- First Option
    - Making things bigger. So, square that may be 100x100, may be 150x150.
- Second Option
    - Making more stuff to fit onto the screen
    - Such as if there are more room in the monitor, such as if we resizing the window.
    - Essentially we, really are cropping it.

### Features
* Added viewport
* Added WindowResize event occuring when minimized and pausing the UI interaction

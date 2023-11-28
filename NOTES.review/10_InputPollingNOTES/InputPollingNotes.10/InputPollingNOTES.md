### Input Polling
- Basically this manages what events are being handled
- Meaning like for key events, this system would are pressing or released
    Example: If we press ctrl + alt, then it would rotate a camera or something like that.
- Essentially we would want to be static meaning that there should only be one of this class.


### Features (Implementations, adding files, etc)
- InputPoll.h and InputPoll.cpp
- Updated Window.h to add getNativeWindow() 
    - Making the return type as void* is because we know that this is going to be returning \
        either HWindow, GLFWwindow, etc.
### Window Management

## Overview
In this phase of the project we discuss and look into how we want to implement our window. Considering that implementing our window class \
it may also be platform dependent. In this case there is WindowsWindow which is implementing a Window interface for Window OS.

### Features
- Added Window.h
    - Window.h contains Windows properties such as title, width, and height for now
- Added WindowsWindow.h (which is Window interface implemented for Windows OS)
    - WindowData (struct) whichh contains related information to windows
    - This is for GLFW for passing in custom user data and passing to GLFW to handle this \
        kind of information. (just a POD, essentially).

- Updated Application.h and Application.cpp
    - Added window class to start testing if logging and basic window abstraction are working correctly.
    - Create window as a unique pointer because Application class is what will own that window, essentially
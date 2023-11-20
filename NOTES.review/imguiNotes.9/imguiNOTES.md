## Using ImGui and implementing into the Game Engine


## Overview
- Using ImGui to create a layer called ImGuiLayer
    - This layer will be used as the debugger layer
    - Debugger layers are typically so you can do debugging and send logs
        on top of the scene in the game engine
- Integrating imgui with OpenGL3 and GLFW
- Referencing to examples given in imgui
- Looked into how we want our debugging layer on top of our main layer to look
- Implementing how we can update the specific debugger layer.
- 

## Features
- Added ImGuiLayer.h and ImGuiLayer.cpp
- At this phase in the game engine, we are referencing opengl3 implementations in imgui, and \
    the GLFW implementations examples in imgui.
- Added OpenGL/ImGuiOpenGLRenderer.h and OpenGL/ImGuiOpenGLRenderer.cpp
    - Here we add the examples from imgui to show how to use imgui with \
        opengl3 and glfw.
- Implemented App::Get() and static instance
    - The idea is that we only have one application whichh is why we create a static instance.
    - Through these static instance we know there is only one application \
        meaning that thoughhout the codebase we want to call Application::Get() \
        because Application contains important information, like related to display or things like that.


## Errors (Errors that had occurred in thihs phase with initializing ImGui that have been fixed)
- There are errors when putting in "# version 400", so instead we put 120 and that fixed the error
    - If we get error unsupported then we should check in ImGuiLayer.cpp and add a version that is \
        supported.
- There were segfaults when we tried running ImGUi.
    - Solution to this was adding ImGui and along with backends directory together whhen putting them \
        somewhere.
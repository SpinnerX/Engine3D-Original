### ImGui and Viewports features


## Overview 
- In this phase we are looking into using docking and viewports from imgui.
- Docking is essentially how you are able to dock windows to other sides of the windows. Essentially what QDockWidget does, in QT.
- Docking to drag a window outside the primary window, essentially.

## Threading Features ** Future insight **
- Here we will probably have the use of multithreading because of we would want a thread for the renderer, and another thread for the application

## Features added
- Refactored code in ImGuiLayer and LayerStack
- Instead of using std::vector<Layer>::iterator we have that be an unsigned int called _layerInsertIndex.
- This will keep track of the counter whhen we push layers onto the LayerStack
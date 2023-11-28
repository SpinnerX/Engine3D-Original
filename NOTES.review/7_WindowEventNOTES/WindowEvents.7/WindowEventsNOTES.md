# Window Events


### Overview
- Window initially generate events, such as anytime we close the window, handling key events, and things \
like that. Generating events. This notes will be going how we are linking the two systems into windows.
- We should be able to say that whenever an event occurs in our window, we want to create one of our events \
    and dispatch it into our engine. Then if any of the application that wants to handle those events are \
    able to.
- Dispatching all different event types such as key press, releases, mouse press, releases, window resized \
    events, etc.

## Features
- Implementing adding event callbacks in Application.h
- WindowsWindow implementing glfw callback functions
    - Basically now using this to figure out how we grab the onEvent callback in Application.h
- Implemented the event callbacks in WindowsWindow.h
    - Setting GLFW event callbacks and using our EventDispatcher implemented
- Once the events are being logged successfully
    - We create EventDispatcher in onEvent
    - EventDispatcher will essentially be binding std::function<void(Event& e)> callback functions
    - These callback functions are going to be passed into dispatch function in EventDispatcher \
        to execute these events, essentially.
    - NOTED in this case, to not use std::bind because of runtime and compile time overhead
        - std::bind in certain cases takes up a lot of ram, and time during compile and runtime.

## TODO (And things to look into in the long run)
- Implement some kind of polling system, where we can ask for the current state of things
- 
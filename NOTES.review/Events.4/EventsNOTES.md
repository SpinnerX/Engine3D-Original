## Events Notes
- When we create these different events, we are assigning them to contain different categories of events
- Such as what kind of events they handle, which category they belong to
- This is a way we can organize different event types.


## Dispatch Systems in Event Based Systems (Event dispatcher is a way to dispatch different event types)
- Using dispatched systems allow to propagate various events to their callback functions
- This system is a core architecture when developing events
- Dispatchher system is just a way to dispatch events based on their types
- If we receive an event our event function gets called, we receive as a ref.
- We can create an insatnce of thihs class with an event that we receive, then we can call the Dispatch function from this class.


## Features IMplemented
Event.h
- Handling core event features and handler

KeyEvent.h
- Handling key events

MouseEvent.h
- Handling mouse pressed, released, scrolling, and moving events

ApplicationEvent.h

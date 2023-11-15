# Entry Point NOTES
- When developing game engines there are entry points
- Using __attribute__((visibility("default))) to basically specify thaht this class/function/variable be visible to other dynamically linked executables or shared libraries.
- We create EntryPoint.h to contain our actual main
- As Sandbox contain our CreateApplication() it also allows us to create our engine a lot easier
- Looking cleaner.


## Features
- Adding Application.h and Application.cpp
- Adding Core.h
- Adding GameEngine.h
- Adding EntryPoint.h

- We basically utilize __attribute__ allowing us to use classes that is dynamically linked.
- So, in this case we setup our file structures in a way to basically allow to create an entry point.
- EntryPoint.h contains our actual main function.
- This main function will be how we create our game engine, essentially.
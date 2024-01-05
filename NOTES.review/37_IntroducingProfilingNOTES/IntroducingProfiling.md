### Introducing Profiling
* Basically this allows us to measure a few metrics
* This allows us to record things such as CPU Usage (time), also how to analyze that data in a meaningful way
* There's two sides of the coin, collecting data and figuring out what data your wanting and how it is going to be useful to your
    - An example would be wanting to know how long a single frame takes
    - How long clearing rendering takes
* Being able to layout every event happening in the GameEngine and know how long everything is in the Game Engine.
* This way if everything is taking 1 millisecond and there's one function that is taking 5 milliseconds, then that \
    would help you to know how to optimize that specific areas of code.


### What does this mean
* How do I handle this data, and not actually show numbers
* Though, but visually show the data metrics visually.
* Potentially recording specific trends in a data
* Such as what if there is something happening per frame that catches your attention.


### Creating your own profilers (In other words Instrumentation)
* In many cases, it makes more sense in creating your own profilers
* This way you can have a profiling tool that is specific you your application (in this case being the GameEngine itself)
* Meaning that it can be built into your codebase and you might want to utilize other profiling tools because and having a single one for your needs would be more efficient
* Platform-specific issues that can be avoided in trying to have users install tools, when the profiling can be part of the Engine
* This is normally called "Instrumentations"

### Features
* Point for right now is to just try to see if we can get numbers onto the screen
* Outputting data for right now


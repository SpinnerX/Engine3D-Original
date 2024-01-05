### Profiling Instrumentation
* Actually utilizing our profiling system
* Understanding how we may want to use our newly integrated profiling tool


### Profiling Context
* Generally when you're profiling, you're gathering lots of data
* Gathering every single frame, in lots of functions
* Which could mean json files could be quite extensive and can be quite time consuming
    * If the json file were to grow extensively like thousands, and thousands of lines
* Usually you do not want to have a running profile that runs forever, in other words
* Current state of the integrated profiler
    * Is that when we start, we begin the session
    * Where we have a startup, runtime, and shutdown session


* How you do this is by instrumentation.
    * Monitor and profile things that you know are going to be needed
    * DO not profile in functions that are already being monitored


### Features
* Simply went throughout the core game engine code and added RENDER_PROFILE_FUNCTION and RENDER_PROFILE_SCOPE where is needed
* Such as in most of the classes where we implemented logic that would be considered important to profile
* Only time we really do not need to profile is the logging class, and specific classes that help for debugging, and utility to understand the logic flow in the engine. (Applied to other form of applications as well)

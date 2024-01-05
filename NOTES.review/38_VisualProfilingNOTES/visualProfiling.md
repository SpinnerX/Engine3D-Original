### Visual Profilers
* Visually showing your data to your profiler



### Context
* Visual profiling is when you stream data and then visualize the way this data looks to make it more meaningful
* Such as that in this case, we implement a profiling class called Instrumentor
* That generates a json file that we can put into a profiling tool to then showcase visually the time each function the session begins and end at take
* Basically how long those functions these session scope around take (in time).



### Features
* Added Instrumentor.h
* Instrumentor.h contains:
    - Essentially creates a json file
    - And added in entry point
    Instrumentor: class
        - beginSession 
        - endSession
        -  writeProfiler, writeHeader, writeFooter
        - creates a thread for each profiling session


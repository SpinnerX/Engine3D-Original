### Renderer Stats and Batch Renderer Improvements
* Added a way to control the constants values
* Adding resetting the stats in the Engine itself
* Created Statistics class for letting to allow clients to modify the maximum values.
* Looking into potentials error with vertex buffer ptr.
    * Such as that it may overflow, hence wanting to catch that as soon as possible.


### Things experiemented with
* Created multiple begin and ending scenes
* Testing how the textures and colors gradients.
* Stress testing the batch rendering to see how well it can handle the different length in draw calls.
* Testing draw calls and stress testing to see how the engine handle specific changes in how you'll modify the values.

### TODO
* Possibly making a tilemap/world
* Using this as a way in benchmarking for optimization (test cases, essentially)


### Features
* Statistics class
* resetStats function


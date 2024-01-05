### 2D Renderer Textures
* Recently added transforms
* Where for each draw quad they are no longer limit to their fixed size(scale) and position(translation)
* So, now this is where we'll take a look into textures within 2D renderers.
* Adding textures and setting them up for the Renderer

### Core Concepts in Textures in the context of 2D Renderer2DStorage
* There are different approachhes to wanting to have the use of both colors and textures to put on objects
* Such as that there are people that'll put these in their fragment shaders
    * Simply where that if you have a color "white" and you want to tint that over time, by modifying the alpha value
    * Or in cases of you have a color black or wanting to tint red, then you can modify all channels for some thing as that.
* Practically having too many types can become quite complicated as you continue to develop the GameEngine.
* Tinting textures/colors

### Debugging Process (in terms of Debugging Textures)
* When debugging textures is when it isn't black meaning that texture still has data
    * Grey in the case we are using the checkerboard image, is going to be how we also know that it isn't rendering correctly
    * Like in cases that the shape could be one color
    * Or if the texture is black then it can be the same thing where there is something wrong with how you are setting up the textures in your code.

### Some Notes
* Coordinate system

### Features
* Textures support

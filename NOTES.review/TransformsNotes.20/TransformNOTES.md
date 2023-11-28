### Transforms (and how they work)

### Reason (Overview and understanding what they help with)
- Moving forward into understanding how we may want to put objects into the world.
- As to where to put all the objects based on their vertex positions
    - Like if we were to render a square at an origin. (or whatever vertex position assigned t)
- Basically saying that you'd want to render a specific object with a specific transfrom
    - Transforms is called like a "Model Matrix" essentially
    - Like a world matrix describing the position, rotation, and the scale of the actual entity (in the 3D world)
    - This is how objects are placed in their respective places in the world.
- For an object, it may contain full of various vertex positions, and other vertex attributes
    - Including normals, texture coordinates, etc.
    - Where all these vertex positions are really just related to each other.
    - Not relative to the world (not having any effect on vertex positions)
    - When you actually render it inside the 3D world, that is when you apply additional transformations to those vertices \
        that actually tell the computer on where to render on the model (object)
        - This way you are able to utilize the same model to render something else
        - If we had wanted to render according to vertex positions then what would be happening instead is that \
            we'd be modifying the values of the vertex buffer for that object.
        - Where we may be either creating and additional second model of that object (models) or two vertex buffers \
            because we may want one object in another location, the other object in the other location.
            - Which is what we do not want
- What we actually want to do is actually render the same exact set of vertices, and however transform that set of vertices by \
    a certain amount.
    - Whether that is by translation (where it is in the world), rotation (how it's rotated oriented), and scale (how big or small it is)
    - This is put all into a transformation matrix.
    - Where we'll need a transformation matrix for every single object that we wan't to render.

** Something to NOTE **
- Most of the times Game Engines use something called an AC or an Entity Component System, or some kind of composable game objects \
    that have kind of set of components that are composed together into essentially a game object.
    - If we were to look at it like an "Entity Component System", then what this basically means is that everything is a component, and data associated \
        and other systems that are associated with those components.
- Eventually in this phase the GameEngine, will eventually have this be implemented in a some form of ECS (Entity Component System) or CG
    - Though in this context by that point the transform would actually be a component that'll probably (like in most objects)

** Essentially what is happening, by adding some more context here **
- Basically what we are saying is that when we have our mesh material (which in this phase is our shader, and out vertex array atm) \
    which are our geometry at the moment.
    - They'll eventually be collapsed into one mesh object
    - Where we would want to submit that (ref to the mesh) and that render at that particular transform
        - Another thing to NOTE when thinking about this is that transforms HAVE to be per mesh (or per object)
        - Whereas if we looked at the camera, we have the transformation matrix is for the entire scene
        - Whereas for meshes there needs to transforms per mesh/object


### Features
- Added glm::mat4& transform as third param for submit
    - To submit a transformation matrix
- In Sandbox, added testing code to showcase how we take the transform matrix as the third parameter, changes position of the square shape.
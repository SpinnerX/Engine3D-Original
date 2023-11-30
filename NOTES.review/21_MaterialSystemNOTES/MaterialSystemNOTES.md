### Material Systems (These NOTES are just discussion, and more theoretical on how material systems work, and the how, and why)
- Looking into the idea of Material Systems, and understanding how they work.
- How we do operations with materials involve shaders, textures, and utilizing the \
    data in representation to vertex attributes.
- Inputs are called uniforms, which are what materials are.
    - A bunch of uniforms and shaders and data.


### Logic Process
- Allowing to modify specific geometry, or shapes into specific/different colors
- Do that by making a material, then submitting that material with the geometry of that mesh.
- What happens is if you have a mesh/object then you render that class that contains all of your \
    geometry that you actually render.
- When looking at meshes and objects in the world
    - One of the things to look at is, does it make sense if the model itself is aware of the light direction
    - Meaning that the material shouldn't care what the light direction is coming, from because light doesn't really \
        effect the materials on the object/mesh/model itself
    - NOTE when thinking about this, if it is sensible if the model should contiain light direction
        - Which it shouldn't.

** Visual Code Idea for materials **
RendererEngine::MaterialRef material = new RendererEngine::Material(_flatColorShader);
material->set("u_Color", redColor);
squareMesh->setMaterial(material) => Potentially allowing this, as this is what it means to have an instance of that material.

- Idea behind this is, that we should be able to construct a material and use this material to take in a shader.
- Allowing for an easier way to set the information regarding to that material, specifically.

** NOTE ** 
- There are a few concepts of "Materials" and "Material Instances" where you can take an instance of a material.
- because you may want to get the base material, like if making a redColor material (since it is a base color), then \
    being able to apply that to color to a mesh, perhaps.

** Material Instance Context **

- visual code below is to add context in regards to if we have a material instance
- Where we can set a specific mesh to an instance material from a base material, essentially.

RendererEngine::MaterialRef material = new RendererEngine::Material(_flatColorShader);
RendererEngine::MaterialInstanceRef mi = new RendererEngine::MaterialInstanceRef(material);

mi->set("u_Color", redColor);
squareMesh->setMaterial(mi);

- Essentially when we start delving more into materials, we may eventually want to start submitting our material instances like the code below:
- Where it takes a material instance, vertex array, and a transformation matrix.
RendererEngine::submit(mi, _squareVA, transform);


material->set("u_Color", redColor);
squareMesh->setMaterial(material) => Potentially allowing this, as this is what it means to have an instance of that material.
- In the submit function what we would do is bind that material instance, and setting those data and for that instance.


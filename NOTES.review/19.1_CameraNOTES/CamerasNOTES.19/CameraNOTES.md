### Cameras and How they work (Camera architecture)


### Overview

1.) Components for the Cameras
    * Field of View (FOV)
    * Aspect Ratio
    * Transformation Matrix
        - Used to adjust the camera field of view and where the object is currently located
    * Projection Matrix
        - Math Formula => proj(mat) * view(mat) * model(mat) * vertexPos
            - Called/Referred to as TRS (Translation x Rotation x Scale) because order of operation \
                matters.
            - This is how we get the full picture of where our model should be rendered \
                onto our screen
            - This order is the GLM's order
            - In DirectX it is the opposite: vertexPos * model(mat) * view(mat) * proj(mat)
            - To re-iterate the part that matters to thhe camera is "proj x view".

2.) Multiplication
    - What is needed to do with the Math Formula "proj(mat) * view(mat) * model(mat) * vertexPos"
    - "proj x view" can do multiplication in the camera
        - Though there are cases where you do need to know the camera's position
        - Important for calculate vectors for a specific pixel

3.) Model Matrix
    - You can do every thing with "proj(mat) x view(mat)" since every single then that'll be rendered will be using this matrix.
    - Why? Because when you enter the scene, the camera isn't going to move when looking at the scene.
    - "proj x view" would initially be static data.
        - Then the model matrix is going to be the transform of each object that does change \
        - Because that changes and render at different position, "proj(mat) x view(mat) x model(mat) x vertexPos" needs to be done \
            for each object, including the use of VertexPos.
    - This is why we have "proj(mat) x view(mat)" because when we are starting a scene, we are telling that we want to start a scene \
        with this point of view.
    - When we render the object we could technically "vp * model" then do this multiplication for every model.
        - Then into your shader do "model x vertexPos" operation into your vertex shader. Essentially gl_Position().
        - mvp * vertex or you can do vp * model, or even vp * model * vertex
        - If you do this inyour vertex, then essentially you would be doing multiplication per vertex which may not be the worse thing.
        - Rather then if you do it the C++ way, then you would do that operation per object.
            - Also considering that we do not want to keep redoing the operation "proj * view * model" because for the view stuff \
                you can really just do those once for the entire scene rather than keep using that data rather than having \
                to actually do that per vertex. (which is what you'd have to do if we were in the vertex shader)
    - Vertex Shader (VS)
        - Math: vp(proj) * model * vertex
            - Model is needed if you need to know normals into a worls space or something like that.

4.) Summarize
    - What we need to do is...
        - When beginning the scene(camera), we want to submit the vp(view projection) matrix and submit a camera giving us the project matrix
        - It is basically going to either reference the camera, or copy the uniform matrix into a uniform buffer. Then when you start rendering a specific shader \
            typically your renderer would batch shaders together, so your not constantly rebinding shader1, shader2.
        - When you bind shader for first time, you have that data inside your renderer, that is the camera belonging to that specific scene
            - Taking that projection matrix from that and then upload into a shader as a uniform buffer, then rendering all the objects for that shader.
        ** Visualization
        BeginScene (cam) => (VP) -> S1 (shader)
        BeginScene (cam) => (VP) -> S2 (Shader)
    - Essentially this is what BeginScene should be doing
    - In grabbing thhat data, you can either save the view projection data from it, or sending reference to actual camera
        - To be optimal what you can do is copy the data because usually submitted (like in a multi-threaded engine) into a submission \
            taking in a reference to the camera can be quite dangerous.
        - Because the camera location can change, possibly being one frame behind.
        - So it would be best to copy all that data from the camera, then putting that into queue command buffer.
    - Then when we start doing PER OBJECT rendering.
        - This is when we take thhe transformation matrix of that object (model mat) and upload that into the shader.
    
    ** re-iterating **
        - When we have a scene, essentially we have a whole bunch of actual shader uniforms that we need to set that are part of the camera
        - Things like the camera things, environment, lighting, as these are not going to change by per object basis.
            - Referred to as the Render/Scene uniforms.
        - But, then we have a bunch of uniforms that are part of the materials.
            - Such as what material are we rendering, is it metal, plastic, how shiny it is, how much should it reflect, or is it wood, what color is it, etc.
            - Referred to as material uniforms
    - What we need is a BeginScene that takes in a Camera as a parameter like BeginScene(Camera)
        - Getting view projection from the camera
        - Not just getting aspect ratio, but getting the min call distance and max call distance.
        - Defining clipping planes that are near and far clipping planes.
        - Baiscally how close an object can be before getting called, and how far an object have to for it not to get rendered because this creates a "view frustrum" \
            - As a projection matrix that is an inverse of the Camera's transform.
            - Taking this data, we need to put it into our renderer upload.
                - When we start our scene, once submit it
                - Once something gets submitted then that gets rendered.
                - We actually need to see what shader we're submitting thhat mesh/vertex array with when we bind the shader for that, we need to upload the projection \
                    and the actual model matrix
    - As for EndScene() really does (and should not) do anything.
        - Potentially call a glClear, though not a good idea
        - In any case of keeping track whether you are inside a scene or not.
        - _scene = false; or something like that.


### Features (Implemented or Added)
- Added OrthographicCamera
    - Containing projec mat, view mat, position, and rotation
    - Adding a way to set the projection matrix into the Shader class
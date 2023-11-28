### Overview
0.) Vertex Arrays in OpenGL
    - Interestingly enough VertexArrays in OpenGL are kind of weird.

1.) Vertex Arrays
    - Essentially vertex arrays are kind of state containing entities
    - Do not contain any data, whereas vertex buffers and index buffers will contain indices.
        - As these two are your actual buffers, they're memory buffers. These two actually contain your actual data.
    - Vertex Arrays contain references to the Vertex Buffers, or Index Buffers

2.) What happens with Vertex Arrays (basically quick overview of how vertex arrays'll work)
    - When you create a vertex array, you then bind a vertex buffer and index buffer to it.
        - Then those two things live inside that vertex array.
        - What this means essentially is that the vertex array is associated with those vertex buffers, and index buffers.
        - NOT rather that they are copying into the vertex array. (Just means that the vertex/index buffers binded to vertex array just reference to those two data points)
        - Does not control their lifetimes, where if you modify the vertex buffer in the vertex array \
            then the vertex buffer in the vertex array would also get modified exactly the same.
    - Vertex Arrays just have links
        - Essentially Vertex Arrays are just pointers to an existing Vertex buffer, or index buffer.
        - As Vertex Arrays do not own the vertex and index buffer, and the other thing it has is essentially \
            all of the layout kind of information of a vertex buffer.
        - They simply are just referencing to those data.
    ** Example would be **
        - When you have vertex attribute pointers and how we set up a buffer layout class.
        - That is stored per vertex buffer, but that state is STORED into the vertex array.
        - Which means that when you rebind that vertex buffer, you do not need to redefinte it's layer, unless it's changed.
    - Although can work differenyly for multiple vertex buffers because what you can do is have a vertex arrays that contain multiple vertex buffers \
        that may containing different information like one for positions, one for normals, one for bones, etc.
    - In that regards these information are still in the vertex arrays, but what you do is 1. bind vertex array, 2. bind vertex buffer, \
        set the layout for the vertex buffer, then bind your next vertex buffer and set the layer to that next vertex buffer with the \
        vertex array still kind of bound.
    - Vertex arrays are also just not for vertex buffers and its layouts, but also the cases for index buffers for element buffers.

Some thing to NOTE about Vertex Array
- VertexArrays is something that does not necessarily exist in DirectX
- Choice needed to make is abstracting this in a sort of way that works.

3.) Some stuff about unbinding
    - Reasons you'd want unbinding is because in the case that you create another two vertex array instead, the two would be considered as one
    - Which can be dangerous.

### Features
- Setting up VertexArray interface class
- Implementing the OpenGLVertexArray class in platforms dir
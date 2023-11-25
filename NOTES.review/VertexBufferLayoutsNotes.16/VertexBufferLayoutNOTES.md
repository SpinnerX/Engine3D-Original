### Vertex Buffer Layouts


### Overview
- This time looking for a way on how to actually descripbe the layout of the data which
    Example: if we have four bytes could potentially be a float, second four bytes, might be another float, \
             third float could be another float. Taking these three floats in a row that could be our three component \
             vector that describes our vertex position.
- Such as telling how we want things to be rendered, where things should be rendering, etc.
- Having this allows for users using the GameEngine to quickly be able to upload data to the GPU (if needed) \
    or the CPU.
- Allowing for the API to be used in a cleaner fashion (at least that would be the goal in this phase)
- Continue in adding more vertex attributes into the engine
    - Such as arrays containing data for normalizing, and uploading to a vertex buffer.
- Abstracting BufferLayout to utilizing BufferElement and BufferLayout classes.
- Using the ShaderDataType enumeration class that are uint8_t.
- To NOTE, that normalization is good if you are planning on supplying like an unsigned int \
    and you want it to automatically convert it back into a Vec4 of floats, or something like that.

### Features
- Implementing the visual representation of our buffer layout
    ** Example shown below **
        ShaderType is platform rendering API specific that tells us what type this is
        Example: ShaderDataType::Float3 to describe it or something like that.
        This is how we would want to setup our layout
        BufferLayout layout = {
            {ShaderDataType::Float3, "a_Position"},
            {ShaderDataType::Float3, "a_Position"},
            {ShaderDataType::Float3, "a_Position"},
            {ShaderDataType::Float3, "a_Position"}
        }
- BufferElement class used in std::initializer_list<BufferElement> contains the following data
    - Name, ShaderDataType, offset (should be calculated when we know what are data is), size (size of buffer)
    
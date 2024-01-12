### Batch Rendering with Textures and Added Additional Debugging Stuff

### Context and Notes
* Looking how textures work in batch Rendering
* Thinking about limiting factors go into draw quads
    * In this case you cannot do that in textures
    * Look at the limit on GPU's of textures bounded at once
    * Meaning that we have a max texture slot count
    * Which refers that our GPU can only bind x amount of textures





### Features
* Added texture slots to represent the kinds of textures in the texture slots
    * textureSlots: array will contain our ID, and the max of textures lots we can have in that array.
    * 0 means white textures, where everytime this index gets reset to 1 then it'll override other textures


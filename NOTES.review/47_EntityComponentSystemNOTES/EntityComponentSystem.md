### Entity Component System
* Going over the introductions as to how ECS work in game engines
* Also dealing with entities in scenes.


### Context in building one
* ECS's are performance critical and not particularily easy to write
* Basics of an ECS is simple.

### Context and Utilization
* Having our own layer for the ECS.
* Where the back-end implementation will be located at.
* Going to be a wrapper around the ECS.

### NOTES in regarding ECS
* Problem it is your trying to solve
    * Why do you need an ECS?
        * If we had a scene
        * Defining a scene is a container that will hold different objects
        * Objects that'll be referred to as entities (unreal refers to as pawns/actors, unity refers to as game objects)
        * These essentially are things that exist in that scene (container) that does things
        * Though they do different things
            * Like lets say we have an entity that is responsible for managing ui display (such as a score for a game)
            * Or even having an entity that runs some code or a script in the background (entity that you wouldn't see)
            * Where these entities are not going to be rendered, because it has a script attached to it.
        * Having a player
            * Such as having a player that needs to be rendered in some kind of way.
            * That has a behavior that associated to it, where that can also be an entity.
        * Another example is if you have a world
            * Where in that world, may contain walls or obstacles that are considered entities.
* Having a scene
    * Essentially a container that contains data that has to exist somewhere
    * Having to interact with things around it.
    * If you have entities they have to be stored somewhere.
    * While also having to be aware of each other.
        * How they do that is by existing in a scene.
    * Where the entities check if there are other entities around them.
    * If there are and have a collider, then they would have some sort of physics response.
    ** Example **
        * An example is if you have an enemy.
        * The enemy is going to need to be aware of the player in a specific threshold for a radius.
        * Where if the player goes in that certain radius, then the enemy would need to chase the player.
Question: How does the enemy know that there is a player nearby?
    * It is because the enemy belongs to the scene, as well the player also exists within that scene.
    * Then in that scene the enemy is able to query to if any other entity is also existing inside of that scene.
        * Figuring out if that entity is existing and might do the following logic as, if there is a player around the enemy.
        * Then the enemy would first check in that scene if there is anything around them, then to let that enemy(entity) know \
            if it is a player, or has some sort of particular tag associated with that entity
        * Then once the enemy(entity) figures out the existing entity, then it'll activate chase mode (or behaviorial script).

### Important to Note for Scenes
* Having a particular scenes.
*  Once you have a type of scenes, your going to need to figure out being able to store these kinds of entities in an effective way
* While still being able to provide these entities with their required behaviors.
* Other words, an entity can be a number of things
    * Things it could be is a 3D model that can be rendered, a sprite that can be rendered, even having code associated with it that \
        doesn't entirely do anything, even an audio clip that gets played, could be an external source, physics, or even light emissions.

### How do we store entities (possibly in a scene)
* Taking a look as to what entities are and that they can be stored in some kind of way
1.) Entity
    * Defining what an entity possible is?
    * Lets say if we had an array of entities.
    * Where if we had an array of entity, that differs from another.
        * In this case Entity1 (E1), and Entity2 (E2).
        * Where thesee entities are completely different
        * E1 - probably some kind of light.
        * E2 - probably some kind of mesh (audio source)
        * And if you have both of them, how are they entities?
        * How would you still program this?
        * How would you give E1 the behavior of light and treat it as a light
            * To then give the scene the ability and renderer ability to treat that entity as a light
            * Doing everything it has to with that light.
        * While still considering the E2, where this entity has a mesh, and an audio source.
        * Where mesh/audio source exists in some kind of assets.
    * How would you compose these entites from different kinds of features.
    * Looking towards on how we can do these things.
        ** Class Heirarchy **
        * Potentially mandating that every entity has a tag (or a name)
        * Showing the different variations of a few things
        * Instaces where you might want entities that either is both a mesh and audio src.
            * Potentially an entity that may only ever be a mesh.
            * Entity that might even only ever be a light source with its associated data as well.
        
        "class Scene"{
            std::vector<Entity *> entities;
        };

        "class Entity"{
            mat4 transform;
            string tag;
        };

        * Now looking at how to make an Entity that is a light source (like E1)
        "class Light" : public Entity {
            vec3 color;
            float intensity; // direction intensity
            Type type; // that can be the direction, bidirectional
        };
        
        * 
        class "AudioMesh" : public Entity {
            AudioClip* clip;
            Mesh* mesh;
        };

        class Player : public Entity{
        };

        * Reason why this inheritance is a Problem
        * Because you are trying to create new classes that contain certain behaviors
        * Almost impossible to make every combination of possible things because of not knowing what to expect.
        * If you have an entity list, the thing you'd have to do in the Scene is check using onUpdate(Timestep).
        * Where it'll check the behavior associated with that function.

2.) ECS (Components)
* Introduces components
* Everything that we have here (all these entities)
* They are a composition of data or behaviors.
* Like audio mesh.
    * An entity that has an audio and mesh.
    * Instead of creating an entity class.
    * Instead creating a class called something like "AudioComponent", and making this class be data in the AudioMesh.

    ** Example **
    * To potentially showcase the ECS without the inheritance stuff.

    struct "AudioComponent"{
        AudioClip* clip;
    };

    struct MeshComponent{
        Mesh* mesh;
    };

    struct Light{
        vec3 color;
        float intensity;
        Type t;
    };
    
    * NOTE: Instead of containing anything, it'll just contain all the components.
    * LIke a base class called components.
    class "Components"{
        
    };
    
    * NOTE: This will be a way to have a single entity that can have any different kinds of components.
    class Entity{
        mat4 transform;
        string tag;
        std::vector<Component *> components;
    };

    class "AudioMesh" : public Entity{
        AudioClip* clip;
        Mesh* mesh;
    };
* Composition over Inheritance

3.) Performance
* Probably not the best method because of performance.
* This is because what if you were to have 1Million entities in the same scene.
* How would you deal with all of those components.
    * When its time to render this.
    * You'd have to go through all of the entities that have a light component \
        or those entites that have an audio clip.
* For the renderer, maybe you have a script component.
* Where there are entities linked up to a C# script that has an onUpdate function.
* Needing to call that function to make sure the MC is updated.
* Such as that they are particles, or physics based.
* THIS is where we've reached a problem where if you have just a scene
    * And an array of Entities.
    * Inside entities having an array of components.
    * Would not have a vector or an array of components, but rather an unordered_set of components instead.
    * Entities wouldn't have multiple things such as multiple light sources, because it is more of it has it or \
        it doesn't have it.
    * Usually have a light entity that is attached to your mesh entity as a child entity.
    * Where you have a parent entity that moves along the child entity.
* Normally you need one component per entity.

4.) Multiple Entity Components
* Visually if the scene::onUpdate
    * Inside this function you have to go through all the entities.
    * Then inside this function, what if you need to render something.
    * Then you would ask if the entity has a mesh component then to submit the component.
* The problem with a million entities.
* And if you were to have a vector of pointers.
* Which containing pointers that may be pointing to our mesh component, or even transformations.
* Where this is not good for the CPU Cache.

4.) Cache and Memory efficient
* It is important to note.
* If we are not dealing with contiguous memory, then it may need to fetch memory in RAM.
* Meaning reading from a location that is not in any of your CPU cache, that can be an estimation to 200 cpu cycles.
* If you happen to have your memory in one place then its faster, because when you ask the CPU to give you want to take \
    some memory and loading it to CPU regs.
* Then you'd be able to write and read into that cache a lot faster then if you decide. 

* In other words if you have all your data in a single location, as in a single block of memory.
* Then it'll be more faster at reading and writing into your CPU cache.
* When asking your CPU for some memory, it doesn't just get you, that one "int", it'll get you a bunch of memory from what you asked \
    and going forwarrds.
* Collaterally gets you the extra bytes of memory that you didn't even ask it to give.
* It'll be like going to the post office to getting your parcel, when it is literally on your doorstep.
* Meaning that it is much faster accessing it there, then somewhere else.

5.) Point of CPU for retrieving data in a block of memory
* The poing is to take advantage of the fact that our CPU doesn't just give us the data we ask for, but \
    data ahead as well.
* How you take advantage of this is when you are iterating (or using) that data, is by packing all the important stuff \
    close together.
* Be more data-driven, and being more considered about how your data is going to be laid out.
    * Because what this means you'll be able to process your data much faster, then if you were just all over the place.

6.) Way to doing that
* Understanding having a list of entities.
* Knowing that you want all your transform components, mesh components in one spot.
* If you have a contiguous array of meshes.
* You'd be able to iterate that array and submit that to the renderer.
* May need multiple things such as Meshes, and Transforms.
* Might need to update all the scripts through onUpdate.
* You can have something like Transform->Mesh->Transform->Mesh, or differeny memory layouts.
* When your entity has a mesh component, this would essentially mean that you are going to need the transform.
* This is because you need to know where you need to render, and if its active.
* Though if you need to go through all your entities, the question is do you even need to know if it is an entity?
* Or as in which entity is, for rendering.
* Since the Renderer all it would care of is vertex buffer, or the attributes.
    * Regarding renderers, you would basically say "Give me all the meshes existing in this scene".
    * This is how the renderer would render those components.
* Only reason why we have entities is to really associate components with each other.
* By checking if that entity contains a transform component, or even a mesh component.
    * As such even to check if you have a script or even an audio clip associated with it.
    * By that you should be able to say that you have a transform, mesh, and an audio, and a C# script.
    These four components should have some kind of relations.
* This is why we need entities, to be aware of these kinds of relations.
* When the C# script asks to play an audio clip, how would that script know which clip to play.
* Hence, needing to know the relations. Which where entities come into play.

7.) Entity ID
* All an Entity are, is an ID.
* Like a 128 bit universally id. (which is what game engines normally have)
* An entity could even be a number, like Entity = 5.
* This ID allow you to communicate the components within that entity.
* Checking if that specific Entity (lets say 5), have an audio clip.
* Common thing to do is to go through the contiguous array of audio clips.
* Then to just do it that way.


### Context
* In other words, objects would care more about the components rather then the entity itself associated with those components.

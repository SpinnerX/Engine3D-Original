## Serializer
* Used for saving and loading in scenes.

## Dependencies
* Utilizing yaml-cpp for the serializer.

## How to
* Question at hand is, how are serializers written?
* Serializers probably shouldnt be added to the class itself
* Picture serializers as an external thing of the scene, not inside the scene.
    * In the case that not having a single function in serializer in the scene.

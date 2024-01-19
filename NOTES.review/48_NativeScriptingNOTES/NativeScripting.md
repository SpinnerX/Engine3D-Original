### Native Scripting

### Context
* Native scripting would still be in C++.
* Determining native scripting without having to lookup the vtable.
* Instead of doing something like "class CameraController : public ScriptComponent" is because we do not want the code to look in the vtable for a virtual function call.
    * This can be no that performant, and can do better then that. 


### Things added
* Added ScriptComponent
    * Could be C#, or even lua
    * Adding to the camera controller class.
* Adding a way we're able to bind NativeScriptComponent like: "_cameraSecond.addComponent<NativeScriptComponent>()"
    * Not providing an instance, but knowing how this instance is going to be created.
    * Such as that we do not want this instance to be allocated
    * When hitting "play" in the editor, your doing to want to instantiating these script classes like camera controller.
    * What you should be providing, is almost like a blue-print to the NativeScriptComponent.
    * Just providing a blueprint, that can be either lambda's or function pointers.
    * To letting this scenes handle that at the right time.
* For binding the native script component with the class
    * It is done by doing: _cameraSecond.addComponent<NativeScriptComponent>().bind<CameraController>();
    * This is what the API is going to look to bind NativeScriptComponent to the class of our (the user) choice.
    * Adding a behavior class to entity.

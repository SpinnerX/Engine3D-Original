#include <Engine3D/Scene/Entity.h>


namespace Engine3D{

	Entity::Entity(entt::entity handle, Scene* scene) : _entityHandler(handle), _scene(scene) {}
};

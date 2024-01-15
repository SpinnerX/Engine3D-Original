#pragma once

namespace RendererEngine{

	struct TransformComponent{
		glm::mat4 _transform = glm::mat4(1.0f);
		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::mat4& transform) : _transform(transform) {}
			
		operator glm::mat4&() { return _transform; }
		operator const glm::mat4&() const { return _transform; }


	};

	struct SpriteRendererComponent{
		glm::vec4 _color = {1.0f, 1.0f, 1.0f, 1.0f};

		SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent&) = default;
		SpriteRendererComponent(const glm::vec4& color) : _color(color){}
	};


};

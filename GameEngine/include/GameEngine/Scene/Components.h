#pragma once

namespace RendererEngine{
	
	struct TagComponent{
		std::string tag;

		TagComponent() = default;
		TagComponent(const std::string& t) : tag(t){}
		TagComponent(const TagComponent&) = default;
	};

	struct TransformComponent{
		glm::mat4 transform = glm::mat4(1.0f);
		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::mat4& transform) : transform(transform) {}
			
		operator glm::mat4&() { return transform; }
		operator const glm::mat4&() const { return transform; }


	};

	struct SpriteRendererComponent{
		glm::vec4 color = {1.0f, 1.0f, 1.0f, 1.0f};

		SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent&) = default;
		SpriteRendererComponent(const glm::vec4& color) : color(color){}
	};


};

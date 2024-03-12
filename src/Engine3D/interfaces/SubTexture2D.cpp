#include <Engine3D/Engine3DPrecompiledHeader.h>
#include <Engine3D/interfaces/SubTexture2D.h>



namespace Engine3D{

	SubTexture2D::SubTexture2D(const Ref<Texture2D>& texture, const glm::vec2& min, const glm::vec2& max) : _texture(texture) {
		_texCoords[0] = {min.x, min.y};
		_texCoords[1] = {max.x, min.y};
		_texCoords[2] = {max.x, max.y};
		_texCoords[3] = {min.x, max.y};
	}
	
	// Function to just automatically calculate the texture coordinates for the game.
	Ref<SubTexture2D> SubTexture2D::createFromCoords(const Ref<Texture2D>& texture, const glm::vec2& coords, const glm::vec2& spriteSize, const glm::vec2& spriteSizeOffset){
		glm::vec2 min = {(coords.x * spriteSize.x) / texture->getWidth(), (coords.y * spriteSize.y) / texture->getHeight()};
		glm::vec2 max = {((coords.x + spriteSizeOffset.x) * spriteSize.x) / texture->getWidth(), ((coords.y + spriteSizeOffset.y) * spriteSize.y) / texture->getHeight()};

		return CreateRef<SubTexture2D>(texture, min, max);
	}
};

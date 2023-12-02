#include <GameEnginePrecompiledHeader.h>
#include <GameEngine/platforms/OpenGL/OpenGLTexture.h>
#include <GameEngine/image/stb_image.h>

namespace RendererEngine{
    OpenGLTexture2D::OpenGLTexture2D(const std::string& filepath) : _filepath(filepath) {
        coreLogInfo("OpenGLTexture2D Create Called!");
        int width, height, channels;

        // Loading in our image data
        stbi_uc* data = stbi_load(filepath.c_str(), &width, &height, &channels, 0);

        if(data == nullptr){
            coreLogError("Failed to load image as the value was nullptr!");
        }
        else coreLogInfo("Image Data was not nullptr meaning it was valid!");
        render_core_assert(data, "Failed to load image!");

        _width = width;
        _height = height;

        // Uploading data to OpenGL texture
        
		// glCreateTextures(GL_TEXTURE_2D, 1, &_rendererID);
		// glTextureStorage2D(_rendererID, 1, GL_RGB8, _width, _height);

		// glTextureParameteri(_rendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		// glTextureParameteri(_rendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        // // Now uploading the texture
        // glTextureSubImage2D(_rendererID, 0, 0, 0, _width, _height, GL_RGB, GL_UNSIGNED_BYTE, data);


        // Testing Textures for OpenGL code here!
        ///////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////

        // Testing textures for OpenGL
        glGenTextures(1, &_rendererID);

        glActiveTexture(GL_TEXTURE1);

        glPixelStorei(GL_UNPACK_ROW_LENGTH, _width);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data); // free image data stored in CPU
    }

    OpenGLTexture2D::~OpenGLTexture2D(){
        glDeleteTextures(1, &_rendererID);
    }

    // Binding specific slot of this texture
    void OpenGLTexture2D::bind(uint32_t slot) const {
        // printf("Slot: %i\n", slot);
        // glBindTextureUnit(0, _rendererID);
        // glBindTexture(GL_TEXTURE_2D, _rendererID);
    }
};
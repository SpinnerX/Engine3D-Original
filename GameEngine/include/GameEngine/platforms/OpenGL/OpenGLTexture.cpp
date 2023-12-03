#include <GameEnginePrecompiledHeader.h>
#include <GameEngine/platforms/OpenGL/OpenGLTexture.h>
#include <GameEngine/image/stb_image.h>

namespace RendererEngine{
    OpenGLTexture2D::OpenGLTexture2D(const std::string& filepath) : _filepath(filepath) {
        coreLogInfo("OpenGLTexture2D Create Called!");
        int width, height, channels;

        stbi_set_flip_vertically_on_load(1);

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

        GLenum internalData = 0, formatData = 0;

        if(channels == 4){
            internalData = GL_RGBA8;
            formatData = GL_RGBA;
        }
        else if(channels == 3){
            internalData = GL_RGB8;
            formatData = GL_RGB;
        }

        // Testing textures for OpenGL
        glGenTextures(1, &_rendererID); // Equivalent to glCreateTexture (but will segfault though)
        glActiveTexture(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, _rendererID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTexImage2D(GL_TEXTURE_2D, 0, internalData, _width, _height, 0, formatData, GL_UNSIGNED_BYTE, data);

        glGenerateMipmap(GL_TEXTURE_2D);


		stbi_image_free(data); // free image data stored in CPU

        glBindTexture(GL_TEXTURE_2D, 0);
    }

    OpenGLTexture2D::~OpenGLTexture2D(){
        glDeleteTextures(1, &_rendererID);
    }

    // Binding specific slot of this texture
    void OpenGLTexture2D::bind(GLenum slot) const {
        // printf("Slot: %i\n", slot);
        // glBindTextureUnit(slot, _rendererID); // Equivalent to glBindTexture (but will segfault though)
        glBindTexture(slot, _rendererID); // Instead of using this we have to use glBindTexture on Mac
    }
};
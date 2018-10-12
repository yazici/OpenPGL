//
//  Texture.cpp
//  project
//
//  Created by Асиф Мамедов on 12.10.2018.
//  Copyright © 2018 Asif Mamedov. All rights reserved.
//

#include "Texture.hpp"

#include <algorithm>

namespace pgl
{
    TextureParameter::TextureParameter(GLenum MinFilter, GLenum MagFilter, GLenum WrapS, GLenum WrapT) :
        minFilter(MinFilter),
        magFilter(MagFilter),
        wrapS(WrapS),
        wrapT(WrapT)
    {
    }

    Texture::Texture() :
        _texture(0),
        _width(0),
        _height(0),
        _srotageFormat(PixelFormat::BLACK_WHITE),
        _dataFormat(PixelFormat::BLACK_WHITE),
        _data(nullptr)
    {
    }

    Texture::Texture(GLuint width, GLuint height, PixelFormat storFrom, PixelFormat dataForm, TextureParameter texParam, const void* data) :
        Texture(create(width, height, storFrom, dataForm, texParam, data))
    {
    }

    Texture::Texture(Texture&& texture)
    {
        std::swap(_data, texture._data);
        _dataFormat = texture._dataFormat;
        _srotageFormat = texture._srotageFormat;
        _texture = texture._texture;
        _height = texture._height;
        _width = texture._width;
    }
    
    Texture Texture::create(GLuint width, GLuint height, pgl::PixelFormat storFrom, pgl::PixelFormat dataForm, pgl::TextureParameter texParam, const void *data)
    {
        Texture texture;
        
        texture._width = width;
        texture._height = height;
        
        std::memcpy(texture._data, data, width * height);
        
        glGenTextures(1, &texture._texture);
        glBindTexture(GL_TEXTURE_2D, texture._texture);
        glTexStorage2D(GL_TEXTURE_2D, 1, (GLenum) dataForm, width, height);
        
        // TODO: параметр type функции glTexSubImage2D не указан при копировании текстуры.
        // Пока что будет стоять GL_UNSIGNED_BYTE, но в дальнейшем нужно дать пользователю
        // возможность выбирать тип.
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, (GLenum)storFrom, GL_UNSIGNED_BYTE, data);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, texParam.magFilter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texParam.minFilter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, texParam.wrapS);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, texParam.wrapT);
        
        return texture;
    }
    
    void Texture::bind(GLint slot) const noexcept
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, _texture);
    }
    
    void Texture::unbind() const noexcept
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    
    GLuint Texture::width() const noexcept
    {
        return _width;
    }
    
    GLuint Texture::height() const noexcept
    {
        return _height;
    }
}

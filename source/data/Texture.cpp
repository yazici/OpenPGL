//
//  Texture.cpp
//  project
//
//  Created by Асиф Мамедов on 12.10.2018.
//  Copyright © 2018 Asif Mamedov. All rights reserved.
//

#include "Texture.h"

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
        _handle(0),
        _width(0),
        _height(0),
        _srotageFormat(PixelFormat::BLACK_WHITE),
        _dataFormat(PixelFormat::BLACK_WHITE),
        _data(nullptr)
    {
    }

    Texture::Texture(GLuint width, GLuint height, PixelFormat storFrom, PixelFormat dataForm, TextureParameter texParam, GLenum dataType, const void* data) :
        Texture(create(width, height, storFrom, dataForm, texParam, dataType, data))
    {
    }

    Texture::Texture(Texture&& texture)
    {
        std::swap(_data, texture._data);
        _dataFormat = texture._dataFormat;
        _srotageFormat = texture._srotageFormat;
        _handle = texture._handle;
        _height = texture._height;
        _width = texture._width;
    }
    
    /**
     * Функция необходима для выявления размера типа.
     */
    GLint getSize(GLenum type)
    {
        switch (type) {
            case GL_UNSIGNED_BYTE: {
                return 1;
                break;
            }
                
            case GL_BYTE: {
                return 1;
                break;
            }
                
            case GL_UNSIGNED_SHORT: {
                return 2;
                break;
            }
                
            case GL_SHORT: {
                return 2;
                break;
            }
                
            case GL_UNSIGNED_INT: {
                return 4;
                break;
            }
                
            case GL_INT: {
                return 4;
                break;
            }
                
            case GL_FLOAT: {
                return 4;
                break;
            }
        }
        
        return 1;
    }
    
    Texture Texture::create(GLuint width, GLuint height, pgl::PixelFormat storFrom, pgl::PixelFormat dataForm, pgl::TextureParameter texParam, GLenum dataType, const void *data)
    {
        Texture texture;
        
        texture._width = width;
        texture._height = height;
        
        texture._data = new GLbyte [width * height + getSize(dataType)];
        
        std::memcpy(texture._data, data, width * height);
        
        glGenTextures(1, &texture._handle);
        glBindTexture(GL_TEXTURE_2D, texture._handle);
        glTexStorage2D(GL_TEXTURE_2D, 1, (GLenum) storFrom, width, height);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, (GLenum)dataForm, dataType, data);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, texParam.magFilter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texParam.minFilter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, texParam.wrapS);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, texParam.wrapT);
        
        return texture;
    }
    
    void Texture::bind(GLint slot) const noexcept
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, _handle);
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

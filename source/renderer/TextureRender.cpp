//
//  TextureRender.cpp
//  createNoise
//
//  Created by Асиф Мамедов on 19.10.2018.
//  Copyright © 2018 PCG. All rights reserved.
//

#include "TextureRender.h"

namespace pgl
{
    TextureParameter::TextureParameter(GLenum MinFilter, GLenum MagFilter, GLenum WrapS, GLenum WrapT)
    {
    }
    
    TextureRender::TextureRender() :
        _handler(0),
        _width(0),
        _height(0),
        _locked(false),
        _sorageFormat(TextureRender::BLACK_WHITE)
    {
    }
    
    TextureRender::TextureRender(PixelFormat storFrom, uint32_t width, uint32_t height) :
        TextureRender(create(storFrom, width, height))
    {
    }
    
    TextureRender::TextureRender(TextureRender&& textureRender) :
        _handler(textureRender._handler),
        _width(textureRender._width),
        _height(textureRender._height),
        _locked(false),
        _sorageFormat(textureRender._sorageFormat)
    {
        textureRender._handler = 0;
    }
    
    TextureRender::TextureRender(const Texture texture, PixelFormat storFrom, TextureParameter parametr, uint32_t width, uint32_t height) :
        TextureRender(create(texture, storFrom, parametr, width, height))
    {
    }
    
    TextureRender::~TextureRender()
    {
        if (_handler) {
            glDeleteTextures(1, &_handler);
        }
    }
    
    TextureRender TextureRender::create(const Texture texture, PixelFormat storFrom, TextureParameter parametr, uint32_t width, uint32_t height)
    {
        TextureRender textureRender = create(storFrom, width, height);
        
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, texture._format, GL_FLOAT, texture._data);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, parametr.magFilter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, parametr.minFilter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, parametr.wrapS);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, parametr.wrapT);
        
        return textureRender;
    }
    
    TextureRender TextureRender::create(TextureRender::PixelFormat storFrom, uint32_t width, uint32_t height)
    {
        TextureRender textureRender;
        
        glGenTextures(1, &textureRender._handler);
        textureRender._width = width;
        textureRender._height = height;
        textureRender._locked = false;
        textureRender._sorageFormat = storFrom;
        
        glBindTexture(GL_TEXTURE_2D, textureRender._handler);
        glTexStorage2D(GL_TEXTURE_2D, 1, storFrom, width, height);
        
        return textureRender;
    }
    
    void TextureRender::bind(int slot) const noexcept
    {
        if (!_locked) {
            glActiveTexture(GL_TEXTURE0 + slot);
            glBindTexture(GL_TEXTURE_2D, _handler);
        }
    }
    
    void TextureRender::unbind() const noexcept
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    
    uint32_t TextureRender::width() const noexcept
    {
        return _width;
    }
    
    uint32_t TextureRender::height() const noexcept
    {
        return _height;
    }
    
    bool TextureRender::loced() const noexcept
    {
        return _locked;
    }
    
    void TextureRender::lock() noexcept
    {
        _locked = true;
    }
    
    void TextureRender::unlock() noexcept
    {
        _locked = false;
    }
    
    void TextureRender::updateData(const Texture &texture, TextureParameter parametr) noexcept
    {
        if (_locked && _handler) {
            glBindTexture(GL_TEXTURE_2D, _handler);
            glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, _width, _height, texture._format, GL_UNSIGNED_BYTE, texture._data);
            
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, parametr.magFilter);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, parametr.minFilter);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, parametr.wrapS);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, parametr.wrapT);

        }
    }
}

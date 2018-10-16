//
//  TextureRender.cpp
//  PGL
//
//  Created by Асиф Мамедов on 16.10.2018.
//  Copyright © 2018 Asif Mamedov. All rights reserved.
//

#include "TextureRender.h"

namespace pgl
{
    TextureRender::TextureRender() :
        _handler(0),
        _width(0),
        _height(0),
        _locked(false),
        _sorageFormat(PixelFormat::BLACK_WHITE)
    {
    }
    
    TextureRender::TextureRender(Texture texture, PixelFormat storFrom, uint32_t width, uint32_t height) :
        TextureRender(create(texture, storFrom, width, height))
    {
    }
    
    TextureRender::TextureRender(TextureRender&& textureRender) :
        _handler(textureRender._height),
        _width(textureRender._width),
        _height(textureRender._height),
        _locked(textureRender._locked),
        _sorageFormat(textureRender._sorageFormat)
    {
        textureRender._height = 0;
    }
    
    TextureRender TextureRender::create(Texture texture, PixelFormat storFrom,  uint32_t width, uint32_t height)
    {
        TextureRender textureRender;
        
        textureRender._width = width;
        textureRender._height = height;
        textureRender._locked = false;
        textureRender._sorageFormat = storFrom;
        
        glGenTextures(1, &textureRender._handler);
        glBindTexture(GL_TEXTURE_2D, textureRender._handler);
        glTexStorage2D(GL_TEXTURE_2D, 1, (GLenum)storFrom, width, height);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, (GLenum) texture._format, GL_UNSIGNED_BYTE, texture._data);
        
        glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, texture._parametr.magFilter);
        glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texture._parametr.minFilter);
        glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, texture._parametr.wrapS);
        glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, texture._parametr.wrapT);
        
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
    
    void TextureRender::updateData(const Texture &texture)
    {
        if (_locked && _handler) {
            glBindTexture(GL_TEXTURE_2D, _handler);
            glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, _width, _height, (GLenum) texture._format, GL_UNSIGNED_BYTE, texture._data);
            
            glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, texture._parametr.magFilter);
            glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texture._parametr.minFilter);
            glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, texture._parametr.wrapS);
            glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, texture._parametr.wrapT);
        }
    }
}

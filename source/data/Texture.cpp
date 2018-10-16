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
    TextureParameter::TextureParameter(GLenum MinFilter, GLenum MagFilter, GLenum WrapS, GLenum WrapT)
    {
    }
    
    Texture::Texture() :
        _data(nullptr),
        _width(0),
        _height(0),
        _name("no name"),
        _format(PixelFormat::BLACK_WHITE)
    {
    }
    
    Texture::Texture(string name, uint32_t width, uint32_t height, PixelFormat format, const uint8_t* data, TextureParameter parametr) :
        Texture(create(name, width, height, format, data, parametr))
    {
    }
    
    Texture::Texture(uint32_t width, uint32_t height, PixelFormat format, const uint8_t* data, TextureParameter parametr) :
        Texture (create(width, height, format, data, parametr))
    {
    }
    
    Texture::Texture(Texture&& texture) :
        _data(texture._data),
        _width(texture._width),
        _height(texture._height),
        _name(texture._name),
        _format(texture._format),
        _parametr(texture._parametr)
    {
        texture._data = nullptr;
    }
    
    Texture Texture::create(std::string name, uint32_t width, uint32_t height, pgl::PixelFormat format, const uint8_t* data, TextureParameter parametr)
    {
        Texture texture;
        
        texture._name = name;
        texture._width = width;
        texture._height = height;
        texture._format = format;
        texture._parametr = parametr;
        texture._data = new GLubyte [width * height];
        
        memcpy(texture._data, data, width * height);
        
        return texture;
    }
    
    Texture::~Texture()
    {
        if (_data) {
            delete [] _data;
        }
    }
    
    Texture Texture::create(uint32_t width, uint32_t height, pgl::PixelFormat format, const uint8_t* data, TextureParameter parametr)
    {
        return create("no name", width, height, format, data, parametr);
    }
    
    uint32_t Texture::width() const noexcept
    {
        return _width;
    }
    
    uint32_t Texture::height() const noexcept
    {
        return _height;
    }
    
    string_view Texture::name() const noexcept
    {
        return _name;
    }
    
    void Texture::name(std::string_view name)
    {
        _name = name;
    }
}

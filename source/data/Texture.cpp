#include "Texture.h"

#include <algorithm>

namespace pgl
{
    Texture::Texture() :
        _data(nullptr),
        _width(0),
        _height(0),
        _name("no name"),
        _format(PixelFormat::BLACK_WHITE)
    {
    }
    
    Texture::Texture(string name, uint32_t width, uint32_t height, PixelFormat format, const uint8_t* data) :
        Texture(create(name, width, height, format, data))
    {
    }
    
    Texture::Texture(uint32_t width, uint32_t height, PixelFormat format, const uint8_t* data) :
        Texture (create(width, height, format, data))
    {
    }
    
    Texture::Texture(Texture&& texture)
    {
        std::swap(_data, texture._data);
        _width = texture._width;
        _height = texture._height;
        _name = texture._name;
        _format = texture._format;
    }
    
    Texture Texture::create(std::string name, uint32_t width, uint32_t height, pgl::PixelFormat format, const uint8_t* data)
    {
        Texture texture;
        texture._name = name;
        texture._width = width;
        texture._height = height;
        texture._format = format;
        texture._data = new GLubyte [width * height];
        memcpy(texture._data, data, width * height);
        return texture;
    }
    
    Texture Texture::create(uint32_t width, uint32_t height, pgl::PixelFormat format, const uint8_t* data )
    {
        return create("no name", width, height, format, data);
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

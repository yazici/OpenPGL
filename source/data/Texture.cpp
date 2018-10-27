//
//  Texture.cpp
//  project
//
//  Created by Асиф Мамедов on 12.10.2018.
//  Copyright © 2018 PCG. All rights reserved.
//
#include "Texture.h"

#include <string_view>

#include <exception>

namespace pgl
{
    
    using namespace std;
    
    Texture::Texture() :
        _data(nullptr),
        _width(0),
        _height(0),
        _name("no name"),
        _format(Texture::PixelFormat::BLACK_WHITE)
    {
    }
    
    /**
     * Функция определяет размерность пикселя.
     *
     * @param format формат пикселя
     * @return размер пикселя
     */
    size_t pixelSizeof (Texture::PixelFormat format)
    {
        size_t size = 1;
        
        switch (format) {
            case Texture::PixelFormat::RGB : {
                size = 3;
                break;
            }
                
            case Texture::PixelFormat::RGBA : {
                size = 4;
                break;
            }
                
            case Texture::PixelFormat::BLACK_WHITE : {
                size = 1;
                break;
            }
                
            case Texture::PixelFormat::BGR : {
                size = 3;
                break;
            }
                
            case Texture::PixelFormat::BGRA : {
                size = 4;
                break;
            }
        }
        
        return size;
    }
    
    Texture::Texture(const string_view& name, uint32_t width, uint32_t height, PixelFormat format) :
        Texture(create(name, width, height, format, nullptr))
    {
    }
    
    Texture::Texture(uint32_t width, uint32_t height, PixelFormat format) :
        Texture("no name", width, height, format)
    {
    }
    
    Texture::Texture(const string_view& name, uint32_t width, uint32_t height, PixelFormat format, const uint8_t* data) :
        Texture(create(name, width, height, format, data))
    {
    }
    
    Texture::Texture(uint32_t width, uint32_t height, PixelFormat format, const uint8_t* data) :
        Texture (create(width, height, format, data))
    {
    }
    
    Texture::Texture(const Texture& texture) :
        _data(new GLubyte [texture._width * texture._height * pixelSizeof(texture._format)]),
        _width(texture._width),
        _height(texture._height),
        _name(texture._name),
        _format(texture._format)
    {
        memcpy(_data, texture._data, _width * _height);
    }
    
    Texture::Texture(Texture&& texture) :
        _data(texture._data),
        _width(texture._width),
        _height(texture._height),
        _name(texture._name),
        _format(texture._format)
    {
        texture._data = nullptr;
    }
    
    Texture Texture::create(const string_view& name, uint32_t width, uint32_t height, PixelFormat format, const uint8_t* data)
    {
        Texture texture;
        
        texture._name = name;
        texture._width = width;
        texture._height = height;
        texture._format = format;
        texture._data = new GLubyte [width * height * pixelSizeof(format)];
        
        if (data) {
            memcpy(texture._data, data, width * height * pixelSizeof(format));
        }
        
        return texture;
    }
    
    Texture Texture::create(uint32_t width, uint32_t height, PixelFormat format, const uint8_t* data)
    {
        return create("no name", width, height, format, data);
    }
    
    void Texture::data(const uint8_t *ptrData, uint32_t width, uint32_t height)
    {
        if (!ptrData) {
            throw invalid_argument("pointer is zero");
        }
        
        size_t sizeFormat = pixelSizeof(_format);
        
        if (width * height != _width * _height) {
            if (_data) {
                delete [] _data;
            }
            
            _data = new GLubyte[width * height * sizeFormat];
        }
        
        _width = width;
        _height = height;
        
        memcpy(_data, ptrData, width * height * sizeFormat);
    }
    
    Texture::~Texture()
    {
        if (_data) {
            delete [] _data;
        }
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
    
    Texture::PixelFormat Texture::pixelFormat() const noexcept
    {
        return _format;
    }
    
    ArrayView<GLubyte> Texture::line(uint32_t x)
    {
        if (x >= _width) {
            throw invalid_argument("Crossing the array");
        }
        
        return ArrayView<GLubyte> (_data +(_width * x), _data +(_width * x) + (_height - 1));;
    }
    
    const ArrayView<GLubyte> Texture::line(uint32_t x) const
    {
        if (x >= _width) {
            throw invalid_argument("Crossing the array");
        }
        
        return ArrayView<GLubyte> (_data +(_width * x), _data +(_width * x) + (_height - 1));;
    }
    
    GLubyte& Texture::at(uint32_t x, uint32_t y)
    {
        if (x >= _width || y >= _height) {
            throw invalid_argument("Crossing the array");
        }
        
        return _data[x * _width + y];
    }
    
    GLubyte Texture::at(uint32_t x, uint32_t y) const
    {
        if (x >= _width || y >= _height) {
            throw invalid_argument("Crossing the array");
        }
        
        return _data[x * _width + y];
    }
}

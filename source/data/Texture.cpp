//
//  Texture.cpp
//  project
//
//  Created by Асиф Мамедов on 12.10.2018.
//  Copyright © 2018 PCG. All rights reserved.
//
#include "Texture.h"

#include <string_view>

#include <stdexcept>

#include <iterator>

namespace pgl
{
    
    using namespace std;
    
    using glm::mix;
    
    Texture::Texture(const vec4& backgroundColor) :
        _name("no name"),
        _width(0),
        _height(0),
        _data(nullptr),
        _backgroundColor(backgroundColor)
    {
    }
    
    Texture::Texture(const string_view& name, uint32_t width, uint32_t height, const float* data, const vec4& backgroundColor) :
        _name(name),
        _width(width),
        _height(height),
        _data(new float[width * height * 4]),
        _backgroundColor(backgroundColor)
    {
        if (data) {
            copy(data, data + (width * height * 4), _data);
        }
    }
    
    Texture::Texture(uint32_t width, uint32_t height, const float* data, const vec4& backgroundColor) :
        Texture ("no name", width, height, data, backgroundColor)
    {
    }
    
    Texture::Texture(const Texture& texture) :
        _name(texture._name),
        _width(texture._width),
        _height(texture._height),
        _data(new float[_width * _height * 4]),
        _backgroundColor(texture._backgroundColor)
    {
        copy(texture._data, texture._data + (texture._width * texture._height * 4), _data);
    }
    
    Texture::Texture(Texture&& texture) :
        _name(texture._name),
        _width(texture._width),
        _height(texture._height),
        _data(texture._data),
        _backgroundColor(texture._backgroundColor)
    {
        texture._data = nullptr;
    }
    
    void Texture::data(const float* ptrData, uint32_t width, uint32_t height)
    {
        if (!ptrData) {
            throw invalid_argument("pointer is zero");
        }
        
        if (width * height != _width * _height) {
            if (_data) {
                delete [] _data;
            }
            
            _data = new float[width * height * 4];
        }
        
        _width = width;
        _height = height;
        
        copy(ptrData, ptrData + (width * height * 4), _data);
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
    
    void Texture::backgroundColor(const vec4 &color)
    {
        _backgroundColor = color;
    }
    
    vec4 Texture::backgroundColor() const noexcept
    {
        return _backgroundColor;
    }
    
    string_view Texture::name() const noexcept
    {
        return _name;
    }
    
    void Texture::name(std::string_view name)
    {
        _name = name;
    }
    
    
    ArrayView<float> Texture::line(uint32_t x)
    {
        if (x >= _width) {
            throw invalid_argument("Crossing the array");
        }
        
        return ArrayView<float> (_data +(_width * x * 4), _data +(_width * x) + (_height * 4 - 1));
    }
    
    const ArrayView<float> Texture::line(uint32_t x) const
    {
        if (x >= _width) {
            throw invalid_argument("Crossing the array");
        }
        
        return ArrayView<float> (_data +(_width * x * 4), _data +(_width * x) + (_height * 4 - 1));
    }
    
    Texture::Texel Texture::at(uint32_t x, uint32_t y)
    {
        if (x >= _width || y >= _height) {
            throw invalid_argument("Crossing the array");
        }
        
        return Texel(&_data[(x * _width + y) * 4]);
    }
    
    const Texture::Texel Texture::at(uint32_t x, uint32_t y) const
    {
        if (x >= _width || y >= _height) {
            throw invalid_argument("Crossing the array");
        }
        
        return Texel(&_data[(x * _width + y) * 4]);
    }
    
    void Texture::Texel::red(uint8_t r) noexcept
    {
        _texel[0] = r;
    }
    
    void Texture::Texel::green(uint8_t g) noexcept
    {
        _texel[1] = g;
    }
    
    void Texture::Texel::blue(uint8_t b) noexcept
    {
        _texel[2] = b;
    }
    
    void Texture::Texel::alpha(uint8_t a) noexcept
    {
        _texel[3] = a;
    }
    
    float Texture::Texel::red() const noexcept
    {
        return _texel[0];
    }
    
    float Texture::Texel::green() const noexcept
    {
        return _texel[1];
    }
    
    float Texture::Texel::blue() const noexcept
    {
        return _texel[2];
    }
    
    float Texture::Texel::alpha() const noexcept
    {
        return _texel[3];
    }
    
    void Texture::blend(const Texture &tex, float a1, float a2) noexcept
    {
        size_t size1 = _width * _height, size2 = tex._width * tex._height;
        
        for (size_t i = 0, size = (size1 < size2 ? size1 : size2) * 4; i < size; i++) {
            _data[i] *= a1;
            _data[i] += tex._data[i] * a1;
        }
    }
    
    void Texture::blend(const Texture &tex, float a)
    {
        size_t size1 = _width * _height, size2 = tex._width * tex._height;
        
        for (size_t i = 0, size = (size1 < size2 ? size1 : size2) * 4; i < size; i++) {
             _data[i] = mix(_data[i], tex._data[i], a);
        }
    }
    
    void Texture::cmbination(const Texture &tex)
    {
        size_t size1 = _width * _height, size2 = tex._width * tex._height;
        
        for (size_t i = 0, size = size1 < size2 ? size1 : size2; i < size; i += 4) {
            if (_data[i] != _backgroundColor.r && _data[i + 1] != _backgroundColor.g && _data[i + 2] != _backgroundColor.b && _data[i + 3] != _backgroundColor.a) {
                if (_data[i] != tex._data[i] && _data[i + 1] != tex._data[i + 1] && _data[i + 2] != tex._data[i + 2] && _data[i + 3] != tex._data[i + 3]) {
                    _data[i] = tex._data[i];
                    _data[i + 1] = tex._data[i + 1];
                    _data[i + 2] = tex._data[i + 2];
                    _data[i + 3] = tex._data[i + 3];
                }
            }
        }
    }
    
    const Texture& Texture::operator = (const Texture &tex)
    {
        if (_width * _height != tex._width * tex._height ) {
            if (_data) {
                delete [] _data;
            }
            
            _data = new float [tex._width * tex._height * 4];
        }
        
        _name = tex._name;
        _width = tex._width;
        _height = tex._height;
        
        copy(tex._data, tex._data + (_width * _height * 4), _data);
        
        return *this;
    }
    
    Texture& Texture::operator |= (const Texture &tex) noexcept
    {
        size_t size1 = tex._width * tex._height, size2 = _width * _height;
        
        for (size_t i = 0, size = (size1 < size2 ? size1 : size2) * 4; i < size; i += 4) {
            if (_data[i] + _data[i + 1] + _data[i + 2] + _data[i + 3] < tex._data[i] + tex._data[i + 1] + tex._data[i + 2] + tex._data[i + 3]) {
                _data[i] = tex._data[i];
                _data[i + 1] = tex._data[i + 1];
                _data[i + 2] = tex._data[i + 2];
                _data[i + 3] = tex._data[i + 3];
            }
        }
        
        return *this;
    }
    
    Texture Texture::operator | (const Texture &tex) const
    {
        Texture temp(*this);
        return (temp |= tex);
    }
    
    Texture& Texture::operator &= (const Texture &tex) noexcept
    {
        size_t size1 = tex._width * tex._height, size2 = _width * _height;
        
        for (size_t i = 0, size = (size1 < size2 ? size1 : size2) * 4; i < size; i += 4) {
            if (_data[i] + _data[i + 1] + _data[i + 2] + _data[i + 3] != tex._data[i] + tex._data[i + 1] + tex._data[i + 2] + tex._data[i + 3]) {
                _data[i] = _data[i + 1] = _data[i + 2] = _data[i + 3] = 0.0f;
            }
        }
        
        return *this;
    }
    
    Texture Texture::operator & (const Texture &tex) const
    {
        Texture temp(*this);
        return (temp &= tex);
    }
    
    Texture& Texture::operator /= (const Texture &tex) noexcept
    {
        size_t size1 = tex._width * tex._height, size2 = _width * _height;
        
        for (size_t i = 0, size = (size1 < size2 ? size1 : size2) * 4; i < size; i += 4) {
            if (_data[i] + _data[i + 1] + _data[i + 2] + _data[i + 3] == tex._data[i] + tex._data[i + 1] + tex._data[i + 2] + tex._data[i + 3]) {
                _data[i] = _data[i + 1] = _data[i + 2] = _data[i + 3] = 0.0f;
            }
        }
        
        return *this;
    }
    
    Texture Texture::operator / (const Texture &tex) const
    {
        Texture temp(*this);
        return (temp /= tex);
    }
}

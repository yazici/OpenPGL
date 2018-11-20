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
    
    Texture::Texture() :
        _name("no name"),
        _width(0),
        _height(0),
        _data(nullptr)
    {
    }
    
    Texture::Texture(const string_view& name, uint32_t width, uint32_t height, const float* data) :
        _name(name),
        _width(width),
        _height(height),
        _data(new GLfloat[width * height * 4])
    {
        if (data) {
            copy(data, data + (width * height * 4), _data);
        }
    }
    
    Texture::Texture(uint32_t width, uint32_t height, const float* data) :
        Texture ("no name", width, height, data)
    {
    }
    
    Texture::Texture(const Texture& texture) :
        _name(texture._name),
        _width(texture._width),
        _height(texture._height),
        _data(new GLfloat[_width * _height * 4])
    {
        copy(texture._data, texture._data + (texture._width * texture._height * 4), _data);
    }
    
    Texture::Texture(Texture&& texture) :
        _name(texture._name),
        _width(texture._width),
        _height(texture._height),
        _data(texture._data)
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
            
            _data = new GLfloat[width * height * 4];
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
    
    string_view Texture::name() const noexcept
    {
        return _name;
    }
    
    void Texture::name(std::string_view name)
    {
        _name = name;
    }
    
    
    ArrayView<GLfloat> Texture::line(uint32_t x)
    {
        if (x >= _width) {
            throw invalid_argument("Crossing the array");
        }
        
        return ArrayView<GLfloat> (_data +(_width * x * 4), _data +(_width * x) + (_height * 4 - 1));
    }
    
    const ArrayView<GLfloat> Texture::line(uint32_t x) const
    {
        if (x >= _width) {
            throw invalid_argument("Crossing the array");
        }
        
        return ArrayView<GLfloat> (_data +(_width * x * 4), _data +(_width * x) + (_height * 4 - 1));
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
    
    void Texture::Texel::red(GLubyte r) noexcept
    {
        _texel[0] = r;
    }
    
    void Texture::Texel::green(GLubyte g) noexcept
    {
        _texel[1] = g;
    }
    
    void Texture::Texel::blue(GLubyte b) noexcept
    {
        _texel[2] = b;
    }
    
    void Texture::Texel::alpha(GLubyte a) noexcept
    {
        _texel[3] = a;
    }
    
    GLfloat Texture::Texel::red() const noexcept
    {
        return _texel[0];
    }
    
    GLfloat Texture::Texel::green() const noexcept
    {
        return _texel[1];
    }
    
    GLfloat Texture::Texel::blue() const noexcept
    {
        return _texel[2];
    }
    
    GLfloat Texture::Texel::alpha() const noexcept
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
    
    const Texture& Texture::operator = (const Texture &tex)
    {
        if (_width * _height != tex._width * tex._height ) {
            if (_data) {
                delete [] _data;
            }
            
            _data = new GLfloat [tex._width * tex._height * 4];
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

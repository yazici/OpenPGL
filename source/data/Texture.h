//
//  Texture.h
//  project
//
//  Created by Асиф Мамедов on 12.10.2018.
//  Copyright © 2018 PCG. All rights reserved.
//

#ifndef _DATA_TEXTURE_H
#define _DATA_TEXTURE_H

#include <GL/glew.h>
#include <string>

#include <data/conteiners/ArrayView.h>

using namespace std;

namespace pgl
{
    class TextureRender;
    
    class Texture
    {
        friend class TextureRender;
        friend class HeightMap;
        
    public:
        
        /**
         * Объединение определяющее формат данных пикселя.
         */
        enum PixelFormat : GLenum
        {
            RGB = GL_RGB,
            RGBA = GL_RGBA,
            BLACK_WHITE = GL_RED,
            BGR = GL_BGR,
            BGRA = GL_BGRA
        };

        
        /**
         * Объединение определяющее тип данных в массиве.
         */
        enum DataType : GLenum
        {
            UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
            UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
            UNSIGNED_INT = GL_UNSIGNED_INT,
            BYTE = GL_BYTE,
            SHORT = GL_SHORT,
            INT = GL_INT,
            FLOAT = GL_FLOAT
        };
        
        /**
         * Класс необходимый для коректной работы с текселем.
         */
        class Texel
        {
        public:
            
            /**
             * Конструктор.
             *
             * @param texel указатель на тексель
             * @param format формат текселя
             */
            Texel(GLubyte* texel, PixelFormat format) :
                _texel(texel),
                _format(format)
            {
            }
            
            void red(GLubyte r);
            void green(GLubyte g);
            void blue(GLubyte b);
            void alpha(GLubyte a);
            
            GLubyte red();
            GLubyte green();
            GLubyte blue();
            GLubyte alpha();
            
            
        private:
            GLubyte* _texel;
            PixelFormat _format;
        };

        
        Texture();
        
        /**
         * Конструктор выделяющий текстуру нужного размера.
         *
         *
         * @param name имя текстуры
         * @param width ширина текстуры
         * @param height высота текстуры
         * @param format формат в котором представляется пиксель в массиве
         */
        Texture(const string_view& name, uint32_t width, uint32_t height, PixelFormat format);
        
        /**
         * Конструктор выделяющий текстуру нужного размера.
         *
         * @param width ширина текстуры
         * @param height высота текстуры
         * @param format формат в котором представляется пиксель в массиве
         */
        Texture(uint32_t width, uint32_t height, PixelFormat format);
        
        /**
         * Конструктор.
         *
         * @param name имя текстуры
         * @param width ширина текстуры
         * @param height высота текстуры
         * @param format формат в котором представляется пиксель в массиве
         * @param data указатель на массив данных
         */
        Texture(const string_view& name, uint32_t width, uint32_t height, PixelFormat format, const uint8_t* data);
        
        /**
         * Конструктор.
         *
         * @param width ширина текстуры
         * @param height высота текстуры
         * @param format формат в котором представляется пиксель в массиве
         * @param data указатель на массив данных
         */
        Texture(uint32_t width, uint32_t height, PixelFormat format, const uint8_t* data);
        
        Texture(Texture&& texture);
        
        Texture(const Texture&);
        
        ~Texture();
        
        /**
         * Функция предназначенная для создания текструы.
         *
         * @param name имя текстуры
         * @param width ширина текстуры
         * @param height высота текстуры
         * @param format формат в котором представляется пиксель в массиве
         * @param data указатель на массив данных
         */
        static Texture create(const string_view& name, uint32_t width, uint32_t height, PixelFormat format, const uint8_t* data);
        
        /**
         * Функция предназначенная для создания текструы.
         *
         * @param width ширина текстуры
         * @param height высота текстуры
         * @param format формат в котором представляется пиксель в массиве
         * @param data указатель на массив данных
         */
        static Texture create(uint32_t width, uint32_t height, PixelFormat format, const uint8_t* data);
        
        /**
         * Метод предназначенный для обновления данных текстуры.
         *
         * @param ptrData указатель на массив с текстурой
         * @param width ширина текстуры
         * @param height высота текстуры
         */
        void data(const uint8_t* ptrData, uint32_t width, uint32_t height);
        
        uint32_t width() const noexcept;
        uint32_t height() const noexcept;
        PixelFormat pixelFormat() const noexcept;
        
        string_view name() const noexcept;
        void name(string_view name);
        
        /**
         * Методы, необходимые для получения срезки из массива,
         * где хранится текстура.
         *
         * @param x индекс строки
         * @throw возникает в случе если произошёл выход за границы срезки
         * @return срезка
         */
        ArrayView<GLubyte> line(uint32_t x);
        const ArrayView<GLubyte> line(uint32_t x) const;
        
        /**
         * Метод с помощью которого можно получать доступ к отдельным тексклям.
         *
         * @param x индкс строки
         * @param y индекс столбца
         * @throw возникает в случе если произошёл выход за границы массива
         * @return элемент текселя(зависит от представления в массиве)
         */
        Texel at(uint32_t x, uint32_t y);
        const Texel at(uint32_t x, uint32_t y) const;
        
    protected:
        GLubyte* _data;
        GLuint _width;
        GLuint _height;
        GLuint _bpp;
        string _name;
        PixelFormat _format;
    };
}

#endif // !_DATA_TEXTURE_H

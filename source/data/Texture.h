//
//  Texture.h
//  project
//
//  Created by Асиф Мамедов on 12.10.2018.
//  Copyright © 2018 PCG. All rights reserved.
//

#ifndef _DATA_TEXTURE_H
#define _DATA_TEXTURE_H

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
         * Класс необходимый для коректной работы с текселем.
         */
        class Texel
        {
        public:
            
            /**
             * Конструктор.
             *
             * @param texel указатель на тексель
             */
            Texel(float* texel) :
            _texel(texel)
            {
            }
            
            void red(uint8_t r) noexcept;
            void green(uint8_t g) noexcept;
            void blue(uint8_t b) noexcept;
            void alpha(uint8_t a) noexcept;
            
            float red() const noexcept;
            float green() const noexcept;
            float blue() const noexcept;
            float alpha() const noexcept;
            
            
        private:
            float* _texel;
        };
        
        
        Texture();
        
        /**
         * Конструктор.
         *
         * @param name имя текстуры
         * @param width ширина текстуры
         * @param height высота текстуры
         * @param data указатель на массив данных
         */
        Texture(const string_view& name, uint32_t width, uint32_t height,  const float* data = nullptr);
        
        /**
         * Конструктор.
         *
         * @param width ширина текстуры
         * @param height высота текстуры
         * @param data указатель на массив данных
         */
        Texture(uint32_t width, uint32_t height, const float* data = nullptr);
        
        Texture(Texture&& texture);
        
        Texture(const Texture&);
        
        ~Texture();
        
        /**
         * Метод предназначенный для обновления данных текстуры.
         *
         * @param ptrData указатель на массив с текстурой
         * @param width ширина текстуры
         * @param height высота текстуры
         * @throw invalid_argument если ptrData равен nullptr
         */
        void data(const float* ptrData, uint32_t width, uint32_t height);
        
        uint32_t width() const noexcept;
        uint32_t height() const noexcept;
        string_view name() const noexcept;
        
        void name(string_view name);
        
        /**
         * Методы, необходимые для получения срезки из массива,
         * где хранится текстура.
         *
         * @param x индекс строки
         * @throw invalid_argument возникает в случе если произошёл выход за границы срезки
         * @return срезка
         */
        ArrayView<float> line(uint32_t x);
        const ArrayView<float> line(uint32_t x) const;
        
        /**
         * Метод с помощью которого можно получать доступ к отдельным тексклям.
         *
         * @param x индкс строки
         * @param y индекс столбца
         * @throw invalid_argument возникает в случе если произошёл выход за границы массива
         * @return элемент текселя(зависит от представления в массиве)
         */
        Texel at(uint32_t x, uint32_t y);
        const Texel at(uint32_t x, uint32_t y) const;
        
        /**
         * Метод, предназначенный для смешивания 2-ч текстур.
         *
         * @param tex текстура для смешивания
         * @param a1 степень присутствия текстуры this
         * @param a2 степень присутствия текстуры tex
         */
        void blend(const Texture& tex, float a1, float a2) noexcept;
        
        const Texture& operator = (const Texture& tex);
        
        /**
         * Перегрузка операторов побитового или.
         *
         * Эти операторы необходимы для объединения  2-х текстур.
         */
        Texture& operator |= (const Texture& tex) noexcept;
        Texture operator | (const Texture& tex) const;
        
        /**
         * Перегрузка операторов побитового и.
         *
         * Эти операторы необходимы для выделения мест пересечения 2-х текстур.
         */
        Texture& operator &= (const Texture& tex) noexcept;
        Texture operator & (const Texture& tex) const;
        
        /**
         * Перегрузка операторов деления.
         *
         * Эти операторы необходимы для выделения таких мест
         * вкоторые входит только текстура this и не входит текстура tex.
         */
        Texture& operator /= (const Texture& tex) noexcept;
        Texture operator / (const Texture& tex) const;
        
    protected:
        string _name;
        uint32_t _width;
        uint32_t _height;
        float* _data;
    };
}

#endif // !_DATA_TEXTURE_H

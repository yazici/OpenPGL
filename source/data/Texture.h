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

#include <glm/glm.hpp>

using namespace std;

using glm::vec4;

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
            
            void red(float r) noexcept;
            void green(float g) noexcept;
            void blue(float b) noexcept;
            void alpha(float a) noexcept;
            
            float red() const noexcept;
            float green() const noexcept;
            float blue() const noexcept;
            float alpha() const noexcept;
            
            
        private:
            float* _texel;
        };
        
        /**
         * Конструктор.
         *
         * @param backgroundColor цвето заднего фона.
         */
        Texture(const vec4& backgroundColor = {0.0f, 0.0f, 0.0f, 0.0f});
        
        /**
         * Конструктор.
         *
         * @param name имя текстуры
         * @param width ширина текстуры
         * @param height высота текстуры
         * @param data указатель на массив данных
         * @param backgroundColor цвет заднего фона
         */
        Texture(const string_view& name, uint32_t width, uint32_t height,  const float* data = nullptr, const vec4& backgroundColor = {0.0f, 0.0f, 0.0f, 0.0f});
        
        /**
         * Конструктор.
         *
         * @param width ширина текстуры
         * @param height высота текстуры
         * @param data указатель на массив данных
         * @param backgroundColor цвет заднего фона
         */
        Texture(uint32_t width, uint32_t height, const float* data = nullptr, const vec4& backgroundColor = {0.0f, 0.0f, 0.0f, 0.0f});
        
        /**
         * Конструктор.
         *
         * @param name имя текстуры
         * @param width ширина текстуры
         * @param height высота текстуры
         * @param backgroundColor цвет заднего фона
         */
        Texture(const string_view& name, uint32_t width, uint32_t height, const vec4& backgroundColor = {0.0f, 0.0f, 0.0f, 0.0f});
        
        /**
         * Конструктор.
         *
         * @param width ширина текстуры
         * @param height высота текстуры
         * @param backgroundColor цвет заднего фона
         */
        Texture(uint32_t width, uint32_t height, const vec4& backgroundColor = {0.0f, 0.0f, 0.0f, 0.0f});
        
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
        
        void backgroundColor(const vec4& color);
        vec4 backgroundColor() const noexcept;
        
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
         * Метод, предназначенный для смешивания 2-х текстур.
         *
         * @param tex текстура для смешивания
         * @param a1 степень присутствия текстуры this
         * @param a2 степень присутствия текстуры tex
         */
        void blend(const Texture& tex, float a1, float a2) noexcept;
        
        /**
         * Метод, предназначенный для смешивания 2-х текстур(предоставляет линейную смесь).
         * Текстура смешивается путём линейной интерполяии между двумя каналами
         * текстур *this и tex.
         *
         * @param tex текстура для смешивания
         * @param a значение для интерполяции
         */
        void blend(const Texture& tex, float a);
        
        /**
         * Данный метод предназначен для объединения 2-х текстур.
         * При объединении будет учитываться цвет фона у текстуры *this(в отличии от оператороы | и |=).
         *
         * @param tex текстура с которрой нужно объединятся
         */
        void combination(const Texture& tex);
        
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
        vec4 _backgroundColor;
    };
}

#endif // !_DATA_TEXTURE_H

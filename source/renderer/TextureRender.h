//
//  TextureRender.hpp
//  PGL
//
//  Created by Асиф Мамедов on 16.10.2018.
//  Copyright © 2018 Asif Mamedov. All rights reserved.
//

#ifndef _TEXTURE_RENDER_H
#define _TEXTURE_RENDER_H

#include "../data/Texture.h"

namespace pgl
{
    /**
     * Данный класс отвечает за отрисовку объекта Texture.
     *
     * В его задачи входт выделение памяти в GPU для помещения туда текстуры
     * и активации текстурного слота для возможности работы с ней шейдерной программы.
     *
     * Помимо этого класс позваляет менять текстуру без перевыделения памяти в GPU
     * (но возможность динамической работы с памятью GPU отсутсвует).
     * Для того что бы это сделать вам необходимо заблокировать объект методом lock()
     * а зтем методом updateData поместить туда новую текстуру. После замены текструы не забудте
     * разблокировать объект методом unlock. Если этого не будет сделано, шейдерные программы
     * не смогут работать с новвой текструой.
     */
    class TextureRender
    {
    public:
        
        /**
         * Определяет внутренний размер (в зависимости от количиства
         * инициализированных каналов и их размера) буфера в котором будт хранится текстура.
         */
        enum : GLenum
        {
            RGB = GL_RGB8,
            RGBA = GL_RGBA8,
            BLACK_WHITE = GL_R8
        };
        
        TextureRender();
        TextureRender(TextureRender&& texureRender);
        
        /**
         * Конструктор.
         *
         * Примечание !!!
         * Выделеннуя в GPU память нельзя будет изменить.
         *
         * @param texture текстура которую нужно выводить
         * @param storFrom формат хранения текстуры
         * @param width ширина текстуры.
         * @param height высота текстуры
         */
        TextureRender(Texture& texture, GLenum storFrom, uint32_t width, uint32_t height);
        
        // TODO: определить поведение конструктора копирования.
        TextureRender(const TextureRender&) = default;
        
        ~TextureRender();
        
        /**
         * Функция преднаязначенная для создание объектов типа TextureRender.
         *
         * Примечание !!!
         * Выделеннуя в GPU память нельзя будет изменить.
         *
         * @param texture текстура которую нужно выводить
         * @param storFrom формат хранения текстуры
         * @param width ширина текстуры.
         * @param height высота текстуры
         */
        static TextureRender create(Texture texture, GLenum storFrom, uint32_t width, uint32_t height);
        
        /**
         * Метод который делает текстуру активной и задаёт ей текструный слот.
         *
         * @param slot текстурный слот.
         */
        void bind(int slot = 0) const noexcept;
        
        /**
         * Метод, делающий текстуру не активной.
         */
        void unbind() const noexcept;
        
        uint32_t width() const noexcept;
        uint32_t height() const noexcept;
        bool loced() const noexcept;
        
        /**
         * Блокирует текстуру.
         */
        void lock() noexcept;
        
        /**
         * Разблокирует текстуру.
         */
        void unlock() noexcept;
        
        /**
         * Данный метод необходим для загрузки новой текстуры.
         * Что бы это сделать не забудте заблокировать объект.
         *
         * @param texture текстура которую нужно загрузить
         */
        void updateData(const Texture& texture) noexcept;
        
    private:
        GLuint _handler;
        GLuint _width;
        GLuint _height;
        bool _locked;
        GLenum _sorageFormat;
    };
}

#endif // !_TEXTURE_RENDER_H

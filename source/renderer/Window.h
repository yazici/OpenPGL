//
//  Window.hpp
//  OpenPGL
//
//  Created by Асиф Мамедов on 26.10.2018.
//

#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <string>
#include <string_view>

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include <iostream>

#include <tuple>

namespace pgl
{
    using std::string;
    using std::string_view;
    using std::tuple;
    
    class Window
    {
    public:
        
        /**
         * Объявление необходимо для выявления определния
         * того с каким буфером мы хотим работать работать
         */
        enum Clear : GLbitfield
        {
            COLOR = GL_COLOR_BUFFER_BIT,
            DEPTH = GL_DEPTH_BUFFER_BIT,
            ACCUM = GL_ACCUM_BUFFER_BIT,
            STENCIL = GL_STENCIL_BUFFER_BIT
        };
        
        /**
         * Объединение определяющее тип выводимого сообщения.
         */
        enum MessegeBoxType
        {
            ERROR = SDL_MESSAGEBOX_ERROR,
            WARNING = SDL_MESSAGEBOX_WARNING,
            INFO = SDL_MESSAGEBOX_INFORMATION
        };
        
        /**
         * Конструктор.
         *
         * @param name название окна
         * @param w ширина окна
         * @param h высота окна
         */
        Window(const string_view& name, int32_t w, int32_t h);
        ~Window();
        
        /**
         * Функция с помощью которой можно задать цвет очистки буфера цвета.
         *
         * @param r канал R (красны)
         * @param g канал G (зелёный)
         * @param b канал B (синий)
         * @param a альфа канал (прозрачный)
         */
        void clearColor(float r, float g, float b, float a = 0.0f) const noexcept;
        
        /**
         * Функция с помощью которой можно задать цвет очистки буфеера накопления.
         *
         * @param r канал R (красны)
         * @param g канал G (зелёный)
         * @param b канал B (синий)
         * @param a альфа канал (прозрачный)
         */
        void clearAccum(float r, float g, float b, float a = 0.0f) const noexcept;
        
        /**
         * Функция с помощью которой можно задать значения для очистки буфера глубины.
         *
         * @param depth значение котроым очищается буффер
         */
        void clearDepth(double depth = 0.0) const noexcept;
        
        /**
         * Функция с помощью которой можно задать значения для буфера трафарета.
         *
         * @param s значение буффера трафарета
         */
        void clearStencil(int32_t s) const noexcept;
        
        /**
         * Функция с помощью которой можно очистить один.
         *
         * @param c тип буфера
         */
        void clear(Clear c = Clear::COLOR) const noexcept;
        
        /**
         * Метод, отображающий неактивный буффер.
         */
        void present() const noexcept;
        
        tuple<int32_t, int32_t> size() const noexcept;
        void size(int32_t w, int32_t h) const noexcept;
        
        /**
         * Метод котроый возвращает размер окна в пикселях.
         */
        tuple<int32_t, int32_t> drawableSize() const;
        
        uint32_t id() const noexcept;
        
        /**
         * Функция предназначенная для вывода сообщеия.
         *
         * @param title титульник сообщения
         * @param text текст передающий основную суть сообщения
         * @param numButtons количество кнопок
         * @param mesType тип сообщения
         * @param ... названия кнопок типа 'const char*'
         * @return номер нажатой кнопки
         */
        static int message(const char *titel, const char *text, Uint8 numButtons, MessegeBoxType mesType ...);
        
        /**
         * Метод предназначенная для вывода сообщеия (этот метод привязан к окну).
         *
         * @param title титульник сообщения
         * @param text текст передающий основную суть сообщения
         * @param mesType тип сообщения
         */
        void messege(const string_view& title, const string_view& text, MessegeBoxType mesType = MessegeBoxType::INFO) const;
        
    private:
        string _name;
        SDL_Window* _window;
        SDL_GLContext _context;
    };
}

#endif // !_WINDOW_H_

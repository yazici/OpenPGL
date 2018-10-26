//
//  InitSystem.h
//  OpenPGL
//
//  Created by Асиф Мамедов on 26.10.2018.
//

#ifndef _INIT_SYSTEM_H_
#define _INIT_SYSTEM_H_

#include <SDL2/SDL.h>

#include <string>
#include <string_view>

namespace pgl::sys
{
    using namespace std;
    
    /**
     * Системный класс.
     *
     * В его обязонности входит инициалзация системы
     * а так же обработка системных ошибок.
     */
    class InitSystem
    {
    public:
        
        /**
         * Функция необходимая для инициализации
         * подсистем(всего их 8) а также установки атрибутов OpenGL.
         */
        static void init();
        
        /**
         * Функция необходимая для очистки всех
         * инициализированных подсистем.
         */
        static void quit() noexcept;
        
        static bool isInit() noexcept;
        
        /**
          * Функция с помощью которой можно узнать об ошибке а программе.
         */
        static string getSysError() noexcept;
        
        /**
         * Функция с помощью которой можно закинуть ошибку.
         */
        static void setSysError(const string_view& error) noexcept;
    private:
        InitSystem();
        InitSystem(const InitSystem&) = delete;
        
        static SDL_bool _init;
    };
}

#endif // !_INIT_SYSTEM_H_

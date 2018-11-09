//
//  InitSystem.cpp
//  OpenPGL
//
//  Created by Асиф Мамедов on 26.10.2018.
//

#include "InitSystem.h"

#include <stdexcept>

#include <GL/glew.h>

namespace pgl::sys
{
    using std::runtime_error;
    
    SDL_bool InitSystem::_init = SDL_FALSE;
    
    void InitSystem::init()
    {
        if (!_init) {
            if (SDL_Init(SDL_INIT_EVERYTHING)) {
                throw runtime_error("SDL library initialization error");
            }
            
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
            SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
            
            _init = SDL_TRUE;
        }
    }
    
    void InitSystem::quit() noexcept
    {
        if (_init) {
            _init = SDL_FALSE;
            SDL_Quit();
        }
    }
    
    bool InitSystem::isInit() noexcept
    {
        return _init;
    }
    
    string InitSystem::getSysError() noexcept
    {
        string err(SDL_GetError());
        SDL_ClearError();
        return err;
    }
    
    void InitSystem::setSysError(const string_view& error) noexcept
    {
        if (!error.empty()) {
            SDL_SetError(error.data());
        }
    }
}

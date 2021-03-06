//
//  Window.cpp
//  OpenPGL
//
//  Created by Асиф Мамедов on 26.10.2018.
//

#include "Window.h"

#include <stdexcept>

namespace pgl
{
    using namespace std;
    
    using std::runtime_error;
    
    Window::Window(const string_view& name, int32_t w, int32_t h) :
        _name(name),
        _window(nullptr)
    {
        _window = SDL_CreateWindow(name.data(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h,
                                   SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
        
        if (!_window) {
            throw runtime_error(InitSystem::getSysError());
        }
        
        _context = SDL_GL_CreateContext(_window);
        
        glewExperimental = GL_TRUE;
        glewInit();
    }
    
    Window::~Window()
    {
        if (_window) {
            SDL_DestroyWindow(_window);
            SDL_GL_DeleteContext(_context);
        }
    }
    
    void Window::clearColor(float r, float g, float b, float a) const noexcept
    {
        glClearColor(r, g, b, a);
    }
    
    void Window::clearAccum(float r, float g, float b, float a) const noexcept
    {
        glClearAccum(r, g, b, a);
    }
    
    void Window::clearDepth(double depth) const noexcept
    {
        glClearDepth(depth);
    }
    
    void Window::clearStencil(int32_t s) const noexcept
    {
        glClearStencil(s);
    }
    
    void Window::clear(Clear c) const noexcept
    {
        glClear(c);
    }
    
    void Window::present() const noexcept
    {
        SDL_GL_SwapWindow(_window);
    }
    
    tuple<int32_t, int32_t> Window::size() const noexcept
    {
        int32_t w, h;
        SDL_GetWindowSize(_window, &w, &h);
        return make_tuple(w, h);
    }
    
    void Window::size(int32_t w, int32_t h) const noexcept
    {
        SDL_SetWindowSize(_window, w, h);
    }
    
    tuple<int32_t, int32_t> Window::drawableSize() const
    {
        if (!InitSystem::isInit()) {
            throw runtime_error("OpenGL is not connected");
        }
        
        int32_t w, h;
        SDL_GL_GetDrawableSize(_window, &w, &h);
        return make_tuple(w, h);
    }
    
    uint32_t Window::id() const noexcept
    {
        return SDL_GetWindowID(_window);
    }
    
    void Window::messege(const string_view& title, const string_view& text, MessegeBoxType mesType) const
    {
        SDL_ShowSimpleMessageBox(mesType, title.data(), text.data(), _window);
    }
}

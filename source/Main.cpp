#include <SDL2/SDL.h>
#include <GL/glew.h>

#include "renderer/ShaderProgram.h"

#include "Sys/InitSystem.h"

#include "renderer/Window.h"

#include "data/Texture.h"

using namespace pgl::sys;
using namespace pgl;

int main(int argc, char **argv)
{
    InitSystem::init();
    
    Window win("PGL", 800, 600);
    
    win.clearColor(0.32f, 0.12f, 0.43f);
    
    Window::messege("OpenPCG", "Open Procedural Generation Library ", Window::MessegeBoxType::INFO, "Maxim", "Asif", "Lena", "Nastya");
    
    SDL_Event event;
    bool stay = true;
    
	ShaderProgram s("shaders/rednerTexture.vert", "shaders/rednerTexture.frag");

    while (stay) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                stay = false;
            }
        }
        
        win.clear();
        win.present();
    }
    
    InitSystem::quit();
    return 0;
}

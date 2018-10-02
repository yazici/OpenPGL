#include <SDL2/SDL.h>
#include <GL/glew.h>

#include "Data/Mesh.h"

int main(int argc, char **argv)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow("OpenPGL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(window);
    glewExperimental = true;
    if (GLEW_OK != glewInit()) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error!", "OpenGL functions can't be loaded.", nullptr);
    }
    SDL_Quit();
    return 0;
}

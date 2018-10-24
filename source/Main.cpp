#include <SDL2/SDL.h>
#include <GL/glew.h>

#include "renderer/ShaderProgram.h"

int main(int argc, char **argv)
{
    SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window *window = SDL_CreateWindow("OpenPGL", 10, 10, 600, 400, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	SDL_GLContext context = SDL_GL_CreateContext(window);
	glewExperimental = true;
	glewInit();

	pgl::ShaderProgram("basic.vert", "basic.frag");

	SDL_Quit();
    return 0;
}

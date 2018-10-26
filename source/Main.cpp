#include <SDL2/SDL.h>
#include <GL/glew.h>

#include "renderer/ShaderProgram.h"

#include "Sys/InitSystem.h"

#include <iostream>

using namespace pgl::sys;

int main(int argc, char **argv)
{
    InitSystem::init();
    InitSystem::quit();
    return 0;
}

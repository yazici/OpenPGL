#include <SDL2/SDL.h>
#include <GL/glew.h>

#include "renderer/ShaderProgram.h"

#include "Sys/InitSystem.h"

#include "renderer/Window.h"

#include "data/Texture.h"
#include "renderer/TextureRender.h"

#include "algorithm/NoiseGenerator2D.h"

using namespace pgl::sys;
using namespace pgl;

int main(int argc, char **argv)
{
    InitSystem::init();
    
    Window win("PGL", 800, 600);
    
    win.clearColor(0.32f, 0.12f, 0.43f);
    
    NoiseGenerator2D noisGen;
    auto heightMap = noisGen.generate(500, 500);
    
    TextureParameter param = {
        GL_LINEAR,
        GL_LINEAR,
        GL_REPEAT,
        GL_REPEAT
    };
    
    ShaderProgram program("/Users/asifmamedov/Desktop/PGL/OpenPGL/source/renderer/shaders/rednerTexture.vert", "/Users/asifmamedov/Desktop/PGL/OpenPGL/source/renderer/shaders/rednerTexture.frag");
    
    program.use();
    
    assert(!glGetError());
    
    TextureRender noiseTextureRender = TextureRender::create(heightMap.texture(), TextureRender::PixelFormat::BLACK_WHITE, param, 500, 500);
    noiseTextureRender.bind();
    
    bool stay = true;
    SDL_Event event;
    
    while (stay) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                stay = false;
            }
        }
        
        win.clear();
        win.present();
    }
    
    InitSystem::quit();
    return 0;
}

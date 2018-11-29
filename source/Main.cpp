#include <SDL2/SDL.h>
#include <GL/glew.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/normal.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "algorithm/NoiseGenerator2D.h"
#include "algorithm/CellularAutomata.h"
#include "algorithm/DiamondSquare.h"
#include "sys/InitSystem.h"
#include "data/Mesh.h"
#include "renderer/Window.h"
#include "renderer/VertexBuffer.h"
#include "renderer/ElementBuffer.h"
#include "renderer/VertexObject.h"
#include "renderer/ShaderProgram.h"

#include "data/Texture.h"
#include "renderer/TextureRender.h"

#include <functional>
#include <cmath>

using namespace pgl;
using namespace glm;
using namespace std;

int main(int argc, char **argv)
{
    sys::InitSystem::init();
    Window window("OpenPGL", 800, 600);
    
    GLfloat pos[] = {
        -1.0f, -1.0f, 0.0f,
        -1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, -1.0f, 0.0f
    };
    
    GLfloat texCoord[] = {
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f
    };
    
    GLuint indices[] {
        1, 0, 2,
        3, 0, 2
    };
    
    EboPtr ebo = ElementBuffer::create(6, indices);
    
    VboPtr posBuf = VertexBuffer::create(4, 12, pos);
    VboPtr texCoordBuf = VertexBuffer::create(4, 8, texCoord);
    
    VaoPtr vao = VertexObject::create();
    
    vao->addElementBuffer(ebo);
    vao->addVertexBuffer(posBuf, AttributeInfo::POSITION);
    vao->addVertexBuffer(texCoordBuf, AttributeInfo::TEXCOORD);
    
    ShaderProgram shader("/Users/asifmamedov/Desktop/PCG/OpenPGL/source/renderer/shaders/rednerTexture.vert", "/Users/asifmamedov/Desktop/PCG/OpenPGL/source/renderer/shaders/rednerTexture.frag");
    shader.use();
    
    function<float (size_t)> l = [](size_t i) {
        return 2.0f;
    };
    
    function<float (size_t)> f = [](size_t i) {
        return 0.5f;
    };
    
    NoiseGenerator2D alg(l, f, 0.5, 12, {-4.0, 14.0}, 1);
    HeightMap map = alg.generate(512, 512);
    
    Texture texture = map.texture();
    
    TextureRender renderTexture (texture, TextureRender::RGBA16_F, TextureParameter(), texture.width(), texture.height());
    
    renderTexture.bind();
    shader.uniform("tex", 0);
    
    SDL_Event event;
    bool run = true;
    
    window.clearColor(0.0f, 0.0f, 0.0f);
    
    while (run) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                run = false;
            }
        }
        
        window.clear();
        vao->draw();
        window.present();
    }
    
    sys::InitSystem::quit();
    return 0;
}

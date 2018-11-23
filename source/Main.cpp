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
#include "renderer/IndexBuffer.h"
#include "renderer/VertexObject.h"

#include <functional>
#include <cmath>

using namespace pgl;
using namespace glm;
using namespace std;

int main(int argc, char **argv)
{
    sys::InitSystem::init();
    Window window("OpenPGL", 800, 600);
    
    Mesh water = Mesh::createPlane(1, 1, 700);
    IndexBuffer *ebo = IndexBuffer::create(water.triangles().size(), water.triangles().data());
    VertexBuffer *position = VertexBuffer::create(sizeof(vec3), water.vertices().size(), water.vertices().data());
    VertexBuffer *normal = VertexBuffer::create(sizeof(vec3), water.normals().size(), water.normals().data());
    VertexObject *waterVao = VertexObject::create("water");
    waterVao->addIndexBuffer(ebo);
    waterVao->addVertexBuffer(position, AttributeInfo::POSITION);
    waterVao->addVertexBuffer(normal, AttributeInfo::NORMAL);
    
//    CellularAutomata::CountNeighbours al = CellularAutomata::FonNeymanNeighbourhood;
//    CellularAutomata alg(0.01f, 2u, 1u, 0u, al);
//    DiamondSquare alg(0.5f, 50.0);
    
    function<float (size_t)> l = [](size_t i) {
        return 2.0f;
    };
    
    function<float (size_t)> f = [](size_t i) {
        return 0.6f;
    };
    NoiseGenerator2D alg(l, f, 240, 12, {-4.0, 14.0});
    HeightMap map = alg.generate(2049, 2049);
    Mesh plane = map.toMesh(.2f);
    
    ebo = IndexBuffer::create(plane.triangles().size(), plane.triangles().data());
    position = VertexBuffer::create(sizeof(vec3), plane.vertices().size(), plane.vertices().data());
    normal = VertexBuffer::create(sizeof(vec3), plane.normals().size(), plane.normals().data());
    
    VertexObject *vao = VertexObject::create("plane");
    vao->addIndexBuffer(ebo);
    vao->addVertexBuffer(position, AttributeInfo::POSITION);
    vao->addVertexBuffer(normal, AttributeInfo::NORMAL);
    
    ShaderProgram shader("shaders/ADS.vert", "shaders/ADS.frag");
    shader.use();
    
    vec3 cameraPosition(0.0f, 180.0f, 350.0f);
    vec3 lightPosition(30.0f, 120.0f, 0.0f);
    vec3 terrainIntensity(0.15f, 0.8f, 0.1f);
    vec3 waterIntensity(0.15f, 0.1f, 0.8f);
    vec3 ka(0.2f);
    vec3 kd(0.7f);
    vec3 ks(0.3f);
    float shininess = 8.0f;
    
    mat4 s = scale(mat4(1.0f), vec3(1.0f));
    mat4 view = lookAt(cameraPosition, vec3(0.0f, 0.0, -1.0f), vec3(0.0f, 1.0f, 0.0f));
    mat4 projection = perspective(radians(45.0f), (float)800 / 600, 0.1f, 800.0f);
    float radian = 0.0f;
    
    bool b_rotate = true;
    SDL_Event event;
    bool run = true;
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glViewport(0, 0, 800, 600);
    glEnable(GL_DEPTH_TEST);
    
    while (run) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                run = false;
            } else if (event.type == SDL_WINDOWEVENT) {
                switch (event.window.event)
                {
                    case SDL_WINDOWEVENT_RESIZED:
                        auto[w, h] = window.size();
                        glViewport(0, 0, w, h);
                        break;
                }
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym)
                {
                    case SDLK_m:
                        b_rotate = !b_rotate;
                        break;
                    case SDLK_l:
                        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                        break;
                    case SDLK_p:
                        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                        break;
                    default:
                        break;
                }
            }
        }
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        radian = b_rotate ? SDL_GetTicks() * 25.0f / 1000.0f : radian;
        mat4 r = rotate(mat4(1.0f), radians(radian), vec3(0.0f, 1.0f, 0.0f));
        mat4 model = r * s;
        mat4 mv = view * model;
        mat3 normalMatrix = mat3(transpose(inverse(mv)));
        mat4 mvp = projection * mv;
		lightPosition.x = 250.0f * cos(SDL_GetTicks() / 1000.0f);
		lightPosition.z = 250.0f * sin(SDL_GetTicks() / 1000.0f);
        
		shader.uniform("uMVP", mvp);
        shader.uniform("uModelView", mv);
        shader.uniform("uNormalMatrix", normalMatrix);
        shader.uniform("uLightPosition", lightPosition);
        
        shader.uniform("uIntensity", terrainIntensity);
        shader.uniform("uKa", ka);
        shader.uniform("uKd", kd);
        shader.uniform("uKs", ks);
        shader.uniform("uShininess", shininess);
        
        vao->draw();
        shader.uniform("uIntensity", waterIntensity);
        waterVao->draw();
        
        window.present();
    }
    
    sys::InitSystem::quit();
    return 0;
}

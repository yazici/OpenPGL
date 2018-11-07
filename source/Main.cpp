#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

#include <chrono>

#include "algorithm/NoiseGenerator2D.h"
#include "algorithm/CellularAutomata.h"
#include "sys/InitSystem.h"
#include "data/Mesh.h"
#include "renderer/Window.h"
#include "renderer/VertexBuffer.h"
#include "renderer/IndexBuffer.h"
#include "renderer/VertexObject.h"

using namespace pgl;

int main(int argc, char **argv)
{
	sys::InitSystem::init();
	Window window("OpenPGL", 800, 600);


//    CellularAutomata::CountNeighbours al = CellularAutomata::FonNeymanNeighbourhood;
//    CellularAutomata alg(0.01f, 2u, 1u, 0u, al);
    
    NoiseGenerator2D alg(2.0, 0.79, 0.2, 11, {12.0, 3.0});
    
	HeightMap map = alg.generate(60, 60);
    
	Mesh plane = map.toMesh();

	IndexBuffer *ebo = IndexBuffer::create(plane.triangles().size(), plane.triangles().data());
	VertexBuffer *position = VertexBuffer::create(sizeof(vec3), plane.vertices().size(), plane.vertices().data());

	VertexObject *vao = VertexObject::create("plane");
	vao->addIndexBuffer(ebo);
	vao->addVertexBuffer(position, AttributeInfo::POSITION);

	ShaderProgram shader("shaders/wtf.vert", "shaders/wtf.frag");
	shader.use();
	shader.uniform("uColor", vec3(0.01, 0.48, 0.1));

	SDL_Event event;
	bool stay = true;
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	mat4 translate = glm::translate(mat4(1.0), vec3(0.0, -1.0, -5.0));
	mat4 perspectiveProj(glm::perspective(45.0f, 800.0f / 600.0f, 0.1f, 200.0f));
	mat4 cameraPos = glm::lookAt(vec3(0.0f, 2.0f, 0.0f), vec3(0.0f, 0.0f, -5.0f), vec3(0.0f, 1.0f, 0.0f));
	glViewport(0, 0, 800, 600);

	while (stay) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT || event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
				stay = false;
			} else if (event.type == SDL_WINDOWEVENT) {
				switch (event.window.event)
				{
				case SDL_WINDOWEVENT_RESIZED:
					auto[w, h] = window.size();
					glViewport(0, 0, w, h);
					break;
				}
			}
		}
		
		float radian = SDL_GetTicks() * 1.0f / 1000.0f;
		mat4 rotate = glm::rotate(translate, radian, vec3(0.0f, 1.0f, 0.0f));
		mat4 mv = translate * rotate;
		shader.uniform("uMVP", perspectiveProj * cameraPos * mv);

		glClear(GL_COLOR_BUFFER_BIT);
		vao->draw();
		window.present();
	}

	sys::InitSystem::quit();
    return 0;
}

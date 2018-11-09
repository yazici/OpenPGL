#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

#include <chrono>

#include "algorithm/NoiseGenerator2D.h"
#include "algorithm/CellularAutomata.h"
#include "algorithm/DiamondSquare.h"
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

	Mesh water = Mesh::createPlane(1, 1, 2100.0f);
	IndexBuffer *ebo = IndexBuffer::create(water.triangles().size(), water.triangles().data());
	VertexBuffer *position = VertexBuffer::create(sizeof(vec3), water.vertices().size(), water.vertices().data());
	VertexObject *waterVao = VertexObject::create("water");
	waterVao->addIndexBuffer(ebo);
	waterVao->addVertexBuffer(position, AttributeInfo::POSITION);

	//CellularAutomata::CountNeighbours al = CellularAutomata::FonNeymanNeighbourhood;
	//CellularAutomata alg(0.01f, 2u, 1u, 0u, al);
    NoiseGenerator2D alg(3.0, 1.1, 120.0f, 3, {-4.0, 14.0});
//  DiamondSquare alg(15.0f);
	HeightMap map = alg.generate(2048, 2048);
	Mesh plane = map.toMesh(1.0f);

	ebo = IndexBuffer::create(plane.triangles().size(), plane.triangles().data());
	position = VertexBuffer::create(sizeof(vec3), plane.vertices().size(), plane.vertices().data());

	VertexObject *vao = VertexObject::create("plane");
	vao->addIndexBuffer(ebo);
	vao->addVertexBuffer(position, AttributeInfo::POSITION);

	ShaderProgram shader("shaders/wtf.vert", "shaders/wtf.frag");
	shader.use();

	SDL_Event event;
	bool stay = true;
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	mat4 m_translate = glm::translate(mat4(1.0f), vec3(0.0f, 0.0f, 0.0f));
	mat4 perspectiveProj(glm::perspective(45.0f, 800.0f / 600.0f, 0.1f, 1000.0f));
	mat4 cameraPos = glm::lookAt(vec3(0.0f, 40.0f, 256.0f), vec3(0.0f, 0.0f, -100.0f), vec3(0.0f, 1.0f, 0.0f));
	bool b_rotate = true;
	float radian = 0.0f, scale = 0.2f;
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

		radian = b_rotate ? SDL_GetTicks() * 1.0f / 1000.0f : radian;
		mat4 m_rotate = glm::rotate(mat4(1.0f), radian, vec3(0.0f, 1.0f, 0.0f));
		mat4 m_scale = glm::scale(mat4(1.0), vec3(scale));
		mat4 mv = m_translate * m_rotate * m_scale;
		shader.uniform("uMVP", perspectiveProj * cameraPos * mv);
		shader.uniform("uColor", vec3(0.01, 0.48, 0.1));
		vao->draw();

		mat4 t = glm::translate(mat4(1.0f), vec3(0.0f, 0.0f, 0.0f));
		mat4 s = glm::scale(mat4(2.0), vec3(scale));
		shader.uniform("uColor", vec3(0.0f, 0.0f, 0.8f));
		shader.uniform("uMVP", perspectiveProj * cameraPos * t * m_rotate * s);
        waterVao->draw();

		window.present();
	}

	sys::InitSystem::quit();
    return 0;
}

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

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

	Mesh plane = Mesh::CreatePlane(4, 5.0f);
	IndexBuffer *ebo = IndexBuffer::create(plane.triangles().size(), plane.triangles().data());
	VertexBuffer *position = VertexBuffer::create(sizeof(vec3), plane.vertices().size(), plane.vertices().data());
	VertexBuffer *normals = VertexBuffer::create(sizeof(vec3), plane.normals().size(), plane.normals().data());

	VertexObject *vao = VertexObject::create("plane");
	vao->addIndexBuffer(ebo);
	vao->addVertexBuffer(position, AttributeInfo::POSITION);
	vao->addVertexBuffer(normals, AttributeInfo::NORMAL);

	mat4 matrixViewModel(1.0f);
	matrixViewModel = glm::translate(matrixViewModel, vec3(0.0, -1.0, -8.0));
	matrixViewModel = glm::rotate(matrixViewModel, 0.349066f, vec3(1.0f, 0.0f, 0.0f));
	mat3 normalMatrx(glm::transpose(matrixViewModel));
	mat4 perspectiveProj(glm::perspective(45.0f, 800.0f / 600.0f, 0.1f, 200.0f));

	vec4 lightPosition(0.0f, 4.0f, -8.0f, 1.0f);
	vec3 ld(0.78f, 0.334f, 0.4345f);
	vec3 kd(1.0f, 1.0f, 1.0f);
	
	ShaderProgram shader("shaders/PhongLighting.vert", "shaders/PhongLighting.frag");
	shader.use();
	
	shader.uniform("NormalMatrix", normalMatrx);
	shader.uniform("ModelViewMatrix", matrixViewModel);
	shader.uniform("ProjectionMatrix", perspectiveProj);
	shader.uniform("Ld", ld);
	shader.uniform("Kd", ld);
	shader.uniform("LightPosition", lightPosition);

	SDL_Event event;
	bool stay = true;
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	while (stay) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT || event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
				stay = false;
			}
		}

		glClear(GL_COLOR_BUFFER_BIT);
		vao->draw();
		window.present();
	}

	sys::InitSystem::quit();
    return 0;
}

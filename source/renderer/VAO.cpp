#include <GL/glew.h>

#include "VAO.h"
#include "../data/Mesh.h"

namespace pgl
{
	VertexObject::VertexObject(const Mesh & mesh)
	{
		glGenVertexArrays(1, &_vao);
		glBindVertexArray(_vao);
		_vbos.resize(3);
		
		_vbos[0].create(mesh.vertices().size() * sizeof(vec3), mesh.vertices().data());
		_vbos[0].bind();
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
		
		_vbos[1].create(mesh.normals().size() * sizeof(vec3), mesh.normals().data());
		_vbos[1].bind();
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

		_vbos[2].create(mesh.uvs().size() * sizeof(vec2), mesh.uvs().data());
		_vbos[2].bind();
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
		_vbos[2].unbind();

		_indices.create(mesh.triangles());
		glBindVertexArray(0);
	}

	VertexObject::~VertexObject()
	{
		glDeleteVertexArrays(1, &_vao);
	}
	
	void VertexObject::draw() const
	{
		glBindVertexArray(_vao);
		glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, nullptr);
	}
}

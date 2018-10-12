#include "VAO.h"

namespace pgl
{
	VertexObject::VertexObject(const Mesh &mesh, const vaoOption& parametrs )
	{
		glGenVertexArrays(1, &_vao);
		glBindVertexArray(_vao);

		_vbos.resize(3);

		if (parametrs.flagVertices)
		{
			/**
			* TODO: VBO работает только типом float.
			*/
			_vbos[0].create(mesh.vertices().size() * sizeof(vec3), mesh.vertices().data());
			_vbos[0].bind();
			glVertexAttribPointer(0, 3, parametrs.dataType, parametrs.normalizeData, parametrs.bufSize,nullptr);
		}

		if (parametrs.flagNormals)
		{
			/**
			* TODO: VBO работает только типом float.
			*/
			_vbos[1].create(mesh.normals().size() * sizeof(vec3), mesh.normals().data());
			_vbos[1].bind();
			glVertexAttribPointer(1, 3, parametrs.dataType, parametrs.normalizeData, parametrs.bufSize, nullptr);
		}


		if (parametrs.flagUV)
		{
			/**
			* TODO: VBO работает только типом float.
			*/
			_vbos[2].create(mesh.uvs().size() * sizeof(vec2), mesh.uvs().data());
			_vbos[2].bind();
			glVertexAttribPointer(1, 2, parametrs.dataType, parametrs.normalizeData, parametrs.bufSize, nullptr);
		}
		
		glBindVertexArray(0);

	}

	VertexObject::~VertexObject()
	{
		glDeleteVertexArrays(1, &_vao);
	}

	void VertexObject::draw() const
	{
		glBindVertexArray(_vao);
	}
}

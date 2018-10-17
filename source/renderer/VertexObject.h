#ifndef _RENDERER_VAO_H
#define _RENDERER_VAO_H

#include <stdint.h>
#include <vector>

#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "Mesh.h"

namespace pgl
{
	using std::vector;

	class Mesh;

	class VertexObject
	{
	public:

		struct VaoOption;

		/**
		* ������� OpenGL ������, ������� ��������� ������ ������ � ������������ ��� ������� ����
		* ������.
		*
		* @param mesh ����������� ��� ������� ���.
		*/
		VertexObject(const Mesh &mesh);

		VertexObject(const VertexObject &o) = delete;

		/**
		* ����������� ���������� ������� � ��� ����� � ����������� ��� ������ ������� OpenGL
		* ������ ������.
		*/
		~VertexObject();

		/**
		* ���������� ��������� �� ��������� ������� (VBO). ����������� ����� �����������, ����
		* VAO ��������� � �������� ��������� (�.�. IsEnable() ���������� true).
		*/
		void draw() const;
		//void Draw(const Shader &shader);

		void addAtribute(const VaoOption& option);

	private:
		vector<VertexBuffer>* _vbos;
		IndexBuffer _indices;
		uint32_t _vao;
	};

	/**
	* ��������� ��������������� ��� �������� ������ 
	* � ������.
	*/
	struct VertexObject::VaoOption
	{
		/**
		* @field index ������ ��������.
		* @field size ���������� ����������� ��������.
		* @field type ��� ������, ������� ����� �������� � �����.
		* @field normalized ������ ���������� (GL_FALSE ��� GL_TRUE).
		* @field stride �������� ����� ����� ����������������� ����������.
		* @field pointer.
		*/

		GLuint index;
		GLuint size;
		GLenum type;
		GLboolean normalized;
		GLsizei stride;
		const GLvoid* pointer;

	};
}

#endif // !_RENDERER_VAO_H
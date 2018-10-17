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
		* Создает OpenGL объект, который описывает данные вершин и используется для рендера этих
		* данных.
		*
		* @param mesh загружаемый для рендера меш.
		*/
		VertexObject(const Mesh &mesh);

		VertexObject(const VertexObject &o) = delete;

		/**
		* Освобождает выделенные ресурсы в том числе и загруженные при помощи функций OpenGL
		* данные вершин.
		*/
		~VertexObject();

		/**
		* Отображает примитивы из связанных буферов (VBO). Отображение будет проводиться, если
		* VAO находится в активном состоянии (т.е. IsEnable() возвращает true).
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
	* Структура предназначенная для описания данных 
	* в буфере.
	*/
	struct VertexObject::VaoOption
	{
		/**
		* @field index индекс атрибута.
		* @field size количество компонентов атрибута.
		* @field type тип данных, которые будут помещены в буфер.
		* @field normalized булева переменная (GL_FALSE или GL_TRUE).
		* @field stride смещение байта между последовательными атрибутами.
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
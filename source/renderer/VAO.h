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

		struct vaoOption;

		/**
		* Создает OpenGL объект, который описывает данные вершин и используется для рендера этих
		* данных.
		*
		* @param mesh загружаемый для рендера меш.
		*/
		VertexObject(const Mesh &mesh, const vaoOption& parametrs);

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

	private:
		vector<VertexBuffer> _vbos;
		IndexBuffer _indices;
		uint32_t _vao;
	};

	/**
	* Структура предназначенная для описания данных 
	* в буфере.
	*/
	struct VertexObject::vaoOption
	{
		/**
		* Три булевых переменные, отвечающие за то,
		* какие данные будут передаватьсяю.
		*/
		bool flagVertices = false;
		bool flagNormals = false;
		bool flagUV = false;

		/**
		* @field bufSize размер буфера
		* @field dataType тип данных, которые будут помещены в буфер
		* @field normalizeData булева переменная (GL_FALSE или GL_TRUE),
		* отвечающая за нормализацию данных в буфере
		*/
		size_t bufSize = 0;
		GLenum dataType = GL_FLOAT;
		GLenum normalizeData = GL_FALSE;
	};
}

#endif // !_RENDERER_VAO_H

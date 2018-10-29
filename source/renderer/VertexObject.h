#ifndef _RENDERER_VERTEXOBJECT_H
#define _RENDERER_VERTEXOBJECT_H

#include <GL/glew.h>
#include <map>
#include <string>
#include <string_view>

#include "renderer/IndexBuffer.h"
#include "renderer/VertexBuffer.h"
#include "renderer/ShaderProgram.h"

namespace pgl
{
	/**
	* Структура предназначенная для описания данных в буфере.
	*
	* @field name имя атрибута в шейдерной программе.
	* @field index индекс атрибута.
	* @field size количество компонентов атрибута.
	* @field type тип данных, которые будут помещены в буфер.
	* @field normalized булева переменная (GL_FALSE или GL_TRUE).
	* @field stride смещение байта между последовательными атрибутами.
	* @field pointer смещение данных от начала хранилища.
	*/
	struct AttributeInfo
	{
		static const AttributeInfo POSITION;
		static const AttributeInfo NORMAL;
		static const AttributeInfo TEXCOORD;
		static const AttributeInfo COLOR;
		
		std::string name;
		GLuint index;
		GLuint size;
		GLenum type;
		GLboolean normalized;
		GLsizei stride;
		GLsizei pointer;

	};

	const AttributeInfo AttributeInfo::POSITION = {"position", 0, 3, GL_FLOAT, GL_FALSE, 0, 0};
	const AttributeInfo AttributeInfo::NORMAL   = {"normal",   1, 3, GL_FLOAT, GL_FALSE, 0, 0};
	const AttributeInfo AttributeInfo::TEXCOORD = {"texCoord", 2, 2, GL_FLOAT, GL_FALSE, 0, 0};
	const AttributeInfo AttributeInfo::COLOR    = {"color",    3, 3, GL_FLOAT, GL_FALSE, 0, 0};

    class VertexObject
    {
    public:

		static VertexObject *create(const std::string_view &name);

        /**
        * Освобождает выделенные ресурсы в том числе и загруженные при помощи функций OpenGL 
        * данные вершин.
        */
        ~VertexObject();

		void addIndexBuffer(IndexBuffer *ebo);

		void addVertexBuffer(const std::string &n, VertexBuffer *buffer);

		void addVertexBuffer(const std::string &n, VertexBuffer *buffer, const AttributeInfo &info);

		void addAttributeInfo(const std::string &buffer, const AttributeInfo &attr);

		void draw(const ShaderProgram &sp) const;

	private:

		VertexObject();

    private:

		std::map<std::string, VertexBuffer *> _vertexBuffers;

		std::map<std::string, int> _attribLocation;
		
		std::string _name;

		IndexBuffer *_ebo;
        
		GLuint _handle;
    };
}

#endif // !_RENDERER_VERTEXOBJECT_H

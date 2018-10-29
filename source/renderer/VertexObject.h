#ifndef _RENDERER_VERTEXOBJECT_H
#define _RENDERER_VERTEXOBJECT_H

#include <GL/glew.h>
#include <map>
#include <string>
#include <string_view>

#include "renderer/IndexBuffer.h"
#include "renderer/VertexBuffer.h"

namespace pgl
{
    class VertexObject
    {
    public:

		static VertexObject *create(const std::string_view &name);

        /**
        * Освобождает выделенные ресурсы в том числе и загруженные при помощи функций OpenGL 
        * данные вершин.
        */
        ~VertexObject();

	private:

		VertexObject();

    private:

		std::map<std::string, VertexBuffer *> _vertexBuffers;

		std::map<std::string, int> _attribLocation;
		
		IndexBuffer *_ebo;
        
		GLuint _handle;
    };

	/**
	* Структура предназначенная для описания данных
	* в буфере.
	*/
	struct AttributeInfo
	{
		/**
		* @field index индекс атрибута.
		* @field size количество компонентов атрибута.
		* @field type тип данных, которые будут помещены в буфер.
		* @field normalized булева переменная (GL_FALSE или GL_TRUE).
		* @field stride смещение байта между последовательными атрибутами.
		* @field pointer смещение данных от начала хранилища.
		*/

		GLuint index;
		GLuint size;
		GLenum type;
		GLboolean normalized;
		GLsizei stride;
		GLsizei pointer;

	};
}

#endif // !_RENDERER_VERTEXOBJECT_H

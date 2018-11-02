#ifndef _RENDERER_VERTEXOBJECT_H
#define _RENDERER_VERTEXOBJECT_H

#include <GL/glew.h>
#include <map>
#include <vector>
#include <string>
#include <string_view>

#include "renderer/IndexBuffer.h"
#include "renderer/VertexBuffer.h"
#include "renderer/ShaderProgram.h"

using namespace std;

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
		static const AttributeInfo VERTEX;

		string name;
		GLuint index;
		GLuint size;
		GLenum type;
		GLboolean normalized;
		GLsizei stride;
		GLsizei pointer;
	};
    
    class VertexObject
    {
    public:

		static VertexObject *create(const string_view &name);

        /**
        * Освобождает выделенные ресурсы в том числе и загруженные при помощи функций OpenGL 
        * данные вершин.
        */
        ~VertexObject();

		void addIndexBuffer(IndexBuffer *ebo);

		void addVertexBuffer(VertexBuffer *buffer, const AttributeInfo &attr);
		void addVertexBuffer(VertexBuffer *buffer, const AttributeInfo &attr1, const AttributeInfo &attr2);
		void addVertexBuffer(VertexBuffer *buffer, const AttributeInfo &attr1, const AttributeInfo &attr2, const AttributeInfo &attr3);
		void addVertexBuffer(VertexBuffer *buffer, const AttributeInfo &attr1, const AttributeInfo &attr2, const AttributeInfo &attr3, const AttributeInfo &attr4);
		void addVertexBuffer(VertexBuffer *buffer, const vector<AttributeInfo> &attribs);

		void draw(const ShaderProgram &sp) const;

		void draw() const;

	private:

		VertexObject();
		
		void _addVertexBuffer(VertexBuffer *buffer);
		void _addAttributeInfo(const AttributeInfo &attr);

    private:

		vector<VertexBuffer *> _vertexBuffers;

		map<string, int> _attribLocation;
		
		string _name;

		IndexBuffer *_ebo;
        
		GLuint _handle;
    };
}

#endif // !_RENDERER_VERTEXOBJECT_H

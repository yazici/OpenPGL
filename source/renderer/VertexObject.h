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

		/**
		* Привязывает буфер индексов.
		* 
		* @param ebo указатель на буфер.
		* @exception invalid_argument, если указатель ebo равен 0.
		*/
		void addIndexBuffer(IndexBuffer *ebo);

		/**
		* Привязывает буфер вершин и настраивает атрибуты вершин, которые ссылаются на буфер.
		* 
		* @param buffer указатель на буфер вершин. Не может принимать значения null.
		* @param attr[1..4] атрибуты вершин, которые будут привязаны к текущему буферу buffer. Атрибуты вершин
		* не должные содержать одинаковые значения поля name. Атрибуты вершин не должны повторяться и не могут 
		* быть привязаны дважды.
		* 
		* @exception invalid_argument, если buffer указывает на null.
		* @exception invalid_argument, если атрибут вершины с таким именем уже привязан к VertexObject.
		*/
		void addVertexBuffer(VertexBuffer *buffer, const AttributeInfo &attr1);
		void addVertexBuffer(VertexBuffer *buffer, const AttributeInfo &attr1, const AttributeInfo &attr2);
		void addVertexBuffer(VertexBuffer *buffer, const AttributeInfo &attr1, const AttributeInfo &attr2, const AttributeInfo &attr3);
		void addVertexBuffer(VertexBuffer *buffer, const AttributeInfo &attr1, const AttributeInfo &attr2, const AttributeInfo &attr3, const AttributeInfo &attr4);

		/**
		* Привязывает буфер вершин и настраивает атрибуты вершин, которые ссылаются на буфер. Вектор атрибутов
		* может заполняться при помощи initializer_list, поэтому возможен такой вызов функции.
		* voa->addVertexBuffer(vbo, {AttributeInfo::POSITION, AttributeInfo::COLOR, AttributeInfo::NORMAL, AttributeInfo::TEXCOORD});
		*
		* @param buffer указатель на буфер вершин. Не может принимать значения null.
		* @param attribs вектор атрибутов. Атрибуты вершин, которые будут привязаны к текущему буферу buffer. 
		* Атрибуты вершин не должные содержать одинаковые значения поля name. Атрибуты вершин не должны повторяться 
		* и не могут быть привязаны дважды.
		*
		* @exception invalid_argument, если buffer указывает на null.
		* @exception invalid_argument, если атрибут вершины с таким именем уже привязан к VertexObject.
		*/
		void addVertexBuffer(VertexBuffer *buffer, const vector<AttributeInfo> &attribs);

		/**
		* Отрисовывает примитивы с использованием указанной шейдерной программы.
		*/
		void draw(const ShaderProgram &sp) const;

		/**
		* Отрисовывает примитивы с учетом того, что нужная шейдерная программа уже является частью рендера.
		*/
		void draw() const;

        void bind() {
            glBindVertexArray(_handle);
        }
        
        void unbind() {
            glBindVertexArray(0);
        }
        
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

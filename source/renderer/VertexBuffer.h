#ifndef _RENDERER_VERTEXBUFFER_H
#define _RENDERER_VERTEXBUFFER_H

#include <GL/glew.h>

namespace pgl
{
    class VertexBuffer
    {
    public:
        
		/**
		* Создает новое хранилище данных размером sizePerVertex * vertNum. Старое хранилище
		* данных будет безвозвратно удалено.
		*
		* @param sizePerVertex размер вершины.
		* @param vertNum количество вершин.
		* @param usage задает ожидаемый шаблон использования буфера данных.
		* @param data указатель на данные, которые будут скопированы в буфер данных.
		* Если указатель NULL, то буфер указанного размера sizePerVertex * vertNum все равно будет создан.
		* @return возвращается указатель на созданный объект.
		*/
		static VertexBuffer *create(int sizePerVertex, int vertNum, const void *data = nullptr, GLenum usage = GL_STATIC_DRAW);

		/**
		* Деструктор объекта. Вызывает операцию очищения буфера данных.
		*/
        ~VertexBuffer();
		
		/**
		* Создает новое хранилище данных размером sizePerVertex * vertNum. Старое хранилище
		* данных будет безвозвратно удалено.
		*
		* @param sizePerVertex размер вершины.
		* @param vertNum количество вершин.
		* @param usage задает ожидаемый шаблон использования буфера данных.
		* @param data указатель на данные, которые будут скопированы в буфер данных.
		* Если указатель NULL, то буфер указанного размера sizePerVertex * vertNum все равно будет создан.
		*/
		void newData(int sizePerVertex, int vertNum, const void *data = nullptr, GLenum usage = GL_STATIC_DRAW);

		/**
		* Обновляет данные в созданом буфере. Обновлению подлежат только данные, которые
		* хранятся в буфере, сам буфер не будет создан заного или перераспределен.
		*
		* @param offset смещение в вершинах от начала буфера где начнется обновление данных.
		* @param len количество вершин, подлежащих обновлению. 
		* @param data указатель на данные, которые будут скопированы в буфер.
		*/
		void updateData(int offset, int len, const void *data);
			
		/**
		* Привязывает буфер к цели GL_ARRAY_BUFFER. 
		*/
        void bind() const noexcept;

		/**
		* Отвязывает буфер.
		*/
        void unbind() const noexcept;

		/**
		* Возвращает количество элементов в буфере.
		* @return количество элементов в буфере.
		*/
		int size() const noexcept;

	private:

		VertexBuffer();

		VertexBuffer(const VertexBuffer &v) = delete;

    private:
        GLuint _handle;
		int _sizePerVertex;
		int _vertNumber;
		GLenum _usage;
    };
}

#endif //!_RENDERER_VERTEXBUFFER_H

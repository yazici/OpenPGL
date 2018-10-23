#ifndef _RENDERER_VERTEXBUFFER_H
#define _RENDERER_VERTEXBUFFER_H

#include <GL/glew.h>

namespace pgl
{
    class VertexBuffer
    {
    public:
        
		/**
		* Метод создает буфер (vertex buffer object) для загрузки и хранения данных,
		* предназначенных для рендера.
		*
		* @param size размер буфера в байтах.
		* @param usage задает ожидаемый шаблон использования буфера данных.
		* @param data указатель на данные, которые будут скопированы в буфер данных.
		* Если указатель NULL, то буфер указанного размера size все равно будет создан.
		* 
		* @return возвращается указатель на созданный объект.
		*/
		static VertexBuffer *create(size_t size, const void *data = nullptr, GLenum usage = GL_STATIC_DRAW);

		/**
		* Деструктор объекта. Вызывает операцию очищения буфера данных.
		*/
        ~VertexBuffer();
		
		/**
		* Создает новое хранилище данных заданого размера size. Старое хранилище
		* данных будет безвозвратно удалено.
		*
		* @param size размер буфера в байтах.
		* @param usage задает ожидаемый шаблон использования буфера данных.
		* @param data указатель на данные, которые будут скопированы в буфер данных.
		* Если указатель NULL, то буфер указанного размера size все равно будет создан.
		*/
		void newData(size_t size, const void *data = nullptr, GLenum usage = GL_STATIC_DRAW);

		/**
		* Обновляет данные в созданом буфере. Обновлению подлежат только данные, которые
		* хранятся в буфере сам буфер не будет создан заного или перераспределен.
		*
		* @param offset смещение от начала буфера где начнется обновление данных.
		* Измеряется в байтах.
		* @param len количество байтов, подлежащих обновлению. 
		* @param data указатель на данные, которые будут скопированы в буфер.
		*/
		void updateData(size_t offset, size_t len, const void *data);
			
		/**
		* Привязывает буфер к цели GL_ARRAY_BUFFER. 
		*/
        void bind() const noexcept;

		/**
		* Отвязывает буфер.
		*/
        void unbind() const noexcept;

	private:

		VertexBuffer();

		VertexBuffer(const VertexBuffer &v) = delete;

    private:
        GLuint _handle;
		size_t _size;
    };
}

#endif //!_RENDERER_VERTEXBUFFER_H

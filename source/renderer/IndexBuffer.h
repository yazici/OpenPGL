#ifndef _RENDERER_INDEXBUFFER_H
#define _RENDERER_INDEXBUFFER_H

#include <GL/glew.h>

namespace pgl
{
    class IndexBuffer
    {
	public:

		/**
		* Метод создает индексный буфер (element buffer object) для загрузки и хранения данных,
		* предназначенных для рендера.
		*
		* @param number количество индексов.
		* @param indx указатель на данные, которые будут скопированы.
		* @param usage ожидаемый шаблон использования буфера данных.
		* Если указатель NULL, то буфер все равно будет создан.
		* @return возвращается указатель на созданный объект.
		*/
		static IndexBuffer *create(int number, const GLuint *indx = nullptr, GLenum usage = GL_STATIC_DRAW);
		
		~IndexBuffer();

		/**
		* Создает новый буфер для хранения number индексов. Старый буфер данных будет безвозвратно удален.
		* 
		* @param number количество индексов.
		* @param indx указатель на данные, которые будут скопированы.
		* @param usage ожидаемый шаблон использования буфера данных.
		*/
		void newData(int number, const GLuint *indx = nullptr, GLenum usage = GL_STATIC_DRAW);

		/**
		* Обновляет индексы в созданом буфере. Обновлению подлежат только данные.
		* 
		* @param offset смещение от начала буфера.
		* @param len количество индексов, которые будут обновлены.
		* @param data массив индексов.
		*/
		void updateData(int offset, int len, const void *data);

		/**
		* Делает буфер текущим.
		*/
		void bind() const noexcept;

		/**
		* Делает буфер не текущим.
		*/
		void unbind() const noexcept;

		/**
		* Возвращает количество индексов хранящихся в буфере.
		* @return количество индексов
		*/
		int size() const noexcept;

	private:

		IndexBuffer();

	private:
		GLuint _handle;
		int _indexNumber;
		GLenum _usage;
    };
}

#endif // !_RENDERER_INDEXBUFFER_H

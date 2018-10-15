#ifndef _RENDERER_INDEXBUFFER_H
#define _RENDERER_INDEXBUFFER_H

#include <vector>
#include <GL/glew.h>

namespace pgl
{
	using std::vector;

    class IndexBuffer
    {
	public:
		IndexBuffer();

		/**
		* @param indx вектор, в котором определены идексы
		*/
		IndexBuffer(const vector<GLuint> &indx);

		/**
		* @param indx массив в котором определены индексы
		* @param size размер массива
		*/
		IndexBuffer(const GLuint *indx, size_t size);

		IndexBuffer(const IndexBuffer &i) = delete;

		~IndexBuffer();

		/**
		* Метод, с помощью котрого инициализируется объект.
		*
		* @param indx вектор, в котором определены идексы
		*/
		void create(const vector<GLuint> &indx);

		/**
		* Метод, с помощью котрого инициализируется объект.
		*
		* @param indx массив в котором определены индексы
		* @param size размер массива
		*/
		void create(const GLuint *indx, size_t size);

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
		size_t size() const noexcept;

	private:
		GLuint _handle;
		size_t _countIndices;
    };
}

#endif // !_RENDERER_INDEXBUFFER_H

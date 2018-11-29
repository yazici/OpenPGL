#ifndef _RENDERER_ELEMENTBUFFER_H
#define _RENDERER_ELEMENTBUFFER_H

#include <memory>

#include "renderer/VertexBuffer.h"

namespace pgl
{
	class ElementBuffer;
	typedef std::unique_ptr<ElementBuffer> EboPtr;

	class ElementBuffer
	{
	public:

		/**
		* Метод создает индексный буфер (element buffer object) для загрузки и хранения данных,
		* предназначенных для рендера.
		*
		* @param number количество индексов.
		* @param elements указатель на данные, которые будут скопированы.
		* @param mode ожидаемый шаблон использования буфера данных.
		* Если указатель NULL, то буфер все равно будет создан.
		* @return возвращается указатель на созданный объект.
		*/
		static EboPtr create(unsigned int number, const unsigned int *elements = nullptr, unsigned int mode = STATIC_DRAW);

		~ElementBuffer();
	
		/**
		* Обновляет индексы в созданом буфере. Обновлению подлежат только данные.
		*
		* @param offset смещение в вершинах от начала буфера где начнется обновление данных.
		* @param number количество вершин, подлежащих обновлению.
		* @param data указатель на данные, которые будут скопированы в буфер.
		*/
		void update(unsigned int offset, unsigned int number, const unsigned int *elements);

		/**
		* Делает буфер текущим.
		*/
		void bind() const;

		/**
		* Делает буфер не текущим.
		*/
		void unbind() const;

		/**
		* Возвращает количество индексов хранящихся в буфере.
		* @return количество индексов
		*/
		unsigned int size() const;

	private:

		ElementBuffer(unsigned int number, const unsigned int *elements, unsigned int mode);

		ElementBuffer(const ElementBuffer &) = delete;

	private:

		unsigned int _ebo;
		unsigned int _number;
	};
}

#endif //!_RENDERER_ELEMENTBUFFER_H

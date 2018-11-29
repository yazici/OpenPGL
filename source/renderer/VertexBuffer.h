#ifndef _RENDERER_VERTEX_BUFFER
#define _RENDERER_VERTEX_BUFFER

#include <memory>
#include <GL/glew.h>

namespace pgl
{
	enum DrawMode : GLenum
	{
		STATIC_DRAW  = GL_STATIC_DRAW,
		DYNAMIC_DRAW = GL_DYNAMIC_DRAW,
		STREAM_DRAW  = GL_STREAM_DRAW
	};

	class VertexBuffer;
	typedef std::unique_ptr<VertexBuffer> VboPtr;

	class VertexBuffer
	{
	public:

		/**
		* Создает новое хранилище данных размером sizePerVertex * vertNum. Старое хранилище
		* данных будет безвозвратно удалено.
		*
		* @param size размер вершины.
		* @param number количество вершин.
		* @param mode задает ожидаемый шаблон использования буфера данных.
		* @param data указатель на данные, которые будут скопированы в буфер данных.
		* Если указатель NULL, то буфер указанного размера size * number все равно будет создан.
		* @return возвращается указатель на созданный объект.
		*/
		static VboPtr create(unsigned int number, unsigned int size, const void *data = nullptr, DrawMode mode = STATIC_DRAW);

		~VertexBuffer();

		/**
		* Обновляет данные в созданом буфере. Обновлению подлежат только данные, которые
		* хранятся в буфере, сам буфер не будет создан заного или перераспределен.
		*
		* @param offset смещение в вершинах от начала буфера где начнется обновление данных.
		* @param number количество вершин, подлежащих обновлению.
		* @param data указатель на данные, которые будут скопированы в буфер.
		*/
		void update(unsigned int offset, unsigned int number, const void *data);

		/**
		* Привязывает буфер.
		*/
		void bind() const;

		/**
		* Отвязывает буфер.
		*/
		void unbind() const;

	private:

		VertexBuffer(unsigned int number, unsigned int size, DrawMode mode, const void *data);

		VertexBuffer(const VertexBuffer &) = delete;

		void init(unsigned int number, unsigned int size, DrawMode mode, const void *data);

	private:
		DrawMode _mode;
		unsigned int _buffer;
		unsigned int _number;
		unsigned int _size;
	};
}

#endif // !_RENDERER_VERTEX_BUFFER

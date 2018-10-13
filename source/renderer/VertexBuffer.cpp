#include <stdexcept>
#include <cassert>

#include "VertexBuffer.h"

namespace pgl
{
	VertexBuffer * VertexBuffer::create(size_t size, GLenum usage, const void *data)
	{
		VertexBuffer *vbo = new VertexBuffer();
		glGenBuffers(1, &(vbo->_handle));

		try {
			vbo->newData(size, usage, data);
		} catch (const std::runtime_error &e) {
			delete vbo;
			std::rethrow_exception(std::current_exception());
		}

		return vbo;
	}

	VertexBuffer::VertexBuffer() : 
		_handle(0),
		_size(0)
	{
	}

	VertexBuffer::~VertexBuffer()
    {
        glDeleteBuffers(1, &_handle);
    }
	
	void VertexBuffer::newData(size_t size, GLenum usage, const void *data)
	{
		assert(_handle);

		_size = size;
		glBindBuffer(GL_ARRAY_BUFFER, _handle);
		glBufferData(GL_ARRAY_BUFFER, size, data, usage);

		int bufferSize = 0;
		glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &bufferSize);

		if ((size_t)bufferSize != size) {
			// FIXME: Пояснение к исключению можно сделать понятнее.
			throw std::runtime_error("OpenGL can't create a buffer with this size.");
		}
	}

	void VertexBuffer::updateData(size_t offset, size_t size, const void *data)
	{
		assert(_handle);

		if (!data) {
			throw std::invalid_argument("Argument 'data' can't be null pointer.");
		}

		glBindBuffer(GL_ARRAY_BUFFER, _handle);
		glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
		// FIXME: Проверка на ошибки.
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void VertexBuffer::bind() const noexcept
    {
        glBindBuffer(GL_ARRAY_BUFFER, _handle);
    }

    void VertexBuffer::unbind() const noexcept
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}
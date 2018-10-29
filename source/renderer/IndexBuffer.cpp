#include <stdexcept>
#include <cassert>
#include "renderer/IndexBuffer.h"

namespace pgl
{
	IndexBuffer::IndexBuffer() :
		_handle(0),
		_indexNumber(0),
		_usage(0)
	{
	}

	IndexBuffer *IndexBuffer::create(int number, const GLuint *indx, GLenum usage)
	{
		IndexBuffer *ibo = new IndexBuffer();

		try {
			ibo->newData(number, indx, usage);
		} catch (const std::exception &e) {
			delete ibo;
			std::rethrow_exception(std::current_exception());
		}

		return ibo;
	}

	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &_handle);
	}

	void IndexBuffer::newData(int number, const GLuint *indx, GLenum usage)
	{
		if (0 >= number) {
			throw std::invalid_argument("The number of indices can't be less than or equal to zero.");
		}

		if (!_handle) {
			glGenBuffers(1, &_handle);
		}

		_indexNumber = number;
		_usage = usage;
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _handle);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indexNumber * sizeof(GLuint), indx, _usage);

		int bufSize = 0;
		glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &bufSize);

		if (bufSize != _indexNumber * sizeof(GLuint)) {
			throw std::runtime_error("OpenGL can't create a buffer with this size.");
		}
	}

	void IndexBuffer::updateData(int offset, int len, const void *data)
	{
		assert(_handle);

		if (!data) {
			throw std::invalid_argument("Argument 'data' can't be null pointer.");
		}

		int s = sizeof(GLuint);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _handle);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset * s, len * s, data);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void IndexBuffer::bind() const noexcept
	{
		assert(_handle);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _handle);
	}

	void IndexBuffer::unbind() const noexcept
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	int IndexBuffer::size() const noexcept
	{
		return _indexNumber;
	}
}

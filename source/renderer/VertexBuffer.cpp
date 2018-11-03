#include <stdexcept>
#include <cassert>

#include "VertexBuffer.h"

namespace pgl
{
	VertexBuffer *VertexBuffer::create(int sizePerVertex, int vertNum, const void *data, GLenum usage)
	{
		VertexBuffer *vbo = new VertexBuffer();

		try {
			vbo->newData(sizePerVertex, vertNum, data, usage);
		} catch (const std::exception &e) {
			delete vbo;
			std::rethrow_exception(std::current_exception());
		}

		return vbo;
	}

	VertexBuffer::VertexBuffer() :
		_handle(0),
		_sizePerVertex(0),
		_vertNumber(0),
		_usage(0)
	{
	}

	VertexBuffer::~VertexBuffer()
    {
        glDeleteBuffers(1, &_handle);
    }
	
	void VertexBuffer::newData(int sizePerVertex, int vertNum, const void *data, GLenum usage)
	{
		if (0 >= sizePerVertex) {
			throw std::invalid_argument("The vertex size can't be less than or equal to zero.");
		} else if (0 >= vertNum) {
			throw std::invalid_argument("The buffer size can't be less than or equal to zero.");
		}

		if (!_handle) {
			glGenBuffers(1, &_handle);
		}

		_sizePerVertex = sizePerVertex;
		_vertNumber = vertNum;
		_usage = usage;
		glBindBuffer(GL_ARRAY_BUFFER, _handle);
		glBufferData(GL_ARRAY_BUFFER, _sizePerVertex * _vertNumber, data, _usage);

		int bufferSize = 0;
		glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &bufferSize);

		if (bufferSize != _sizePerVertex * _vertNumber) {
			throw std::runtime_error("OpenGL can't create a buffer with this size.");
		}
	}

	void VertexBuffer::updateData(int offset, int len, const void *data)
	{
		assert(_handle);

		if (!data) {
			throw std::invalid_argument("Argument 'data' can't be null pointer.");
		}

		glBindBuffer(GL_ARRAY_BUFFER, _handle);
		glBufferSubData(GL_ARRAY_BUFFER, offset * _sizePerVertex, len * _sizePerVertex, data);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void VertexBuffer::bind() const noexcept
    {
		assert(_handle);
        glBindBuffer(GL_ARRAY_BUFFER, _handle);
    }

    void VertexBuffer::unbind() const noexcept
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

	int VertexBuffer::size() const noexcept
	{
		return _vertNumber;
	}
}

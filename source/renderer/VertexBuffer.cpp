#include <stdexcept>
#include <cassert>

#include "renderer/VertexBuffer.h"

namespace pgl
{
	using namespace std;

	VboPtr VertexBuffer::create(unsigned int number, unsigned int size, const void *data, DrawMode mode)
	{
		VertexBuffer *buf = new VertexBuffer(number, size, mode, data);
		return VboPtr(buf);
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &_buffer);
	}

	VertexBuffer::VertexBuffer(unsigned int number, unsigned int size, DrawMode mode, const void *data)
		: _buffer(0),
		  _size(0),
		  _number(0)
	{
		if (0 == number) {
			throw invalid_argument("Argument 'number' can't be equal to zero.");
		} else if (0 == size) {
			throw invalid_argument("Argument 'size' can't be equal to zero.");
		}

		_number = number;
		_size = size;
		_mode = mode;

		glGenBuffers(1, &_buffer);

		if (!_buffer) {
			throw runtime_error("OpenGL can't allocate resources.");
		}

		glBindBuffer(GL_ARRAY_BUFFER, _buffer);
		glBufferData(GL_ARRAY_BUFFER, _size * _number, data, _mode);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void VertexBuffer::update(unsigned int offset, unsigned int number, const void * data)
	{
		assert(_buffer);

		if (0 == number) {
			throw invalid_argument("Argument 'number' can't be equal to zero.");
		} else if (offset + number > _number) {
			throw invalid_argument("Argument out of range.");
		}

		glBindBuffer(GL_ARRAY_BUFFER, _buffer);
		glBufferSubData(GL_ARRAY_BUFFER, offset * _size, number * _size, data);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void VertexBuffer::bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, _buffer);
	}

	void VertexBuffer::unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	
}

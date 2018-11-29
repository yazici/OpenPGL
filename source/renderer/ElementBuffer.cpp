#include <stdexcept>
#include <cassert>

#include "renderer/ElementBuffer.h"

namespace pgl
{
	EboPtr ElementBuffer::create(unsigned int number, const unsigned int *elements, unsigned int mode)
	{
		ElementBuffer *ebo = new ElementBuffer(number, elements, mode);
		return EboPtr(ebo);
	}

	ElementBuffer::ElementBuffer(unsigned int number, const unsigned int *elements, unsigned int mode)
		: _ebo(0),
		  _number(number)
	{
		if (0 == _number) {
			throw std::invalid_argument("Argument 'number' can't be equal to zero.");
		}

		glGenBuffers(1, &_ebo);

		if (!_ebo) {
			throw std::runtime_error("OpenGL can't allocate resources.");
		}

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, _number * sizeof(GLuint), elements, mode);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	ElementBuffer::~ElementBuffer()
	{
		assert(_ebo);
		glDeleteBuffers(1, &_ebo);
	}

	void ElementBuffer::update(unsigned int offset, unsigned int number, const unsigned int *elements)
	{
		assert(_ebo);

		if (0 == number) {
			throw std::invalid_argument("Argument 'number' can't be equal to zero.");
		} else if (offset + number > _number) {
			throw std::invalid_argument("Argument out of range.");
		}

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset * sizeof(GLuint), number * sizeof(GLuint), elements);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void ElementBuffer::bind() const
	{
		assert(_ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
	}

	void ElementBuffer::unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}	
	
	unsigned int ElementBuffer::size() const
	{
		assert(_ebo);
		return _number;
	}
}

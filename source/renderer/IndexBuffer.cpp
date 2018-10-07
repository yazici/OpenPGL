#include "IndexBuffer.h"

namespace pgl
{
	IndexBuffer::IndexBuffer() :
		_ebo(0u),
		_countIndices(0)
	{
	}

	IndexBuffer::IndexBuffer(const vector<GLuint>& indx) :
		IndexBuffer()
	{
		create(indx);
	}

	IndexBuffer::IndexBuffer(const GLuint * indx, size_t size) :
		IndexBuffer()
	{
		create(indx, size);
	}

	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &_ebo);
	}
	
	void IndexBuffer::create(const vector<GLuint>& indx)
	{
		create(indx.data(), indx.size());
	}

	void IndexBuffer::create(const GLuint * indx, size_t size)
	{
		if (_ebo) {
			throw std::runtime_error("Index buffer object has been created and can't be created again.");
		} else if (0 >= size) {
			throw std::invalid_argument("The argument size must be greater than 0.");
		} else if (nullptr == indx) {
			throw std::invalid_argument("You passed in a null pointer. The 'indx' argument can't be a null pointer.");
		}

		glGenBuffers(1, &_ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(GLuint), (const void *)indx, GL_STATIC_DRAW);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void IndexBuffer::bind() const noexcept
	{
		if (!_ebo) {
			throw std::runtime_error("The element array buffer was not created.");
		}

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
	}

	void IndexBuffer::unbind() const noexcept
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	size_t IndexBuffer::size() const noexcept
	{
		return _countIndices;
	}
}

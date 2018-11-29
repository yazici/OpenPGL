#include <stdexcept>
#include <cassert>
#include <utility>

#include "renderer/VertexObject.h"

namespace pgl
{
	VaoPtr VertexObject::create()
	{
		return VaoPtr(new VertexObject());
	}

	VertexObject::VertexObject()
		: _vao(0)
	{
		glGenVertexArrays(1, &_vao);

		if (!_vao) {
			throw std::runtime_error("OpenGL can't allocate resources.");
		}
	}

	VertexObject::~VertexObject()
	{
		assert(_vao);
		
		/*for (auto &b : _buffers) {
			delete b.release();
		}*/

		glDeleteVertexArrays(1, &_vao);
	}

	void VertexObject::addVertexBuffer(VboPtr &buffer, const AttributeLayout &attribs)
	{
		assert(_vao);
		glBindVertexArray(_vao);
		buffer->bind();
		unsigned int stride = attribs.stride();

		for (size_t i = 0; i < attribs.length(); ++i) {
			auto &a = attribs.get(i);
			glVertexAttribPointer(a.index, a.size, a.type, a.normalize, stride, (const void*)a.pointer);
			glEnableVertexAttribArray(a.index);
		}

		buffer->unbind();
		glBindVertexArray(0);
		_buffers.push_back(std::move(buffer));
	}

	void VertexObject::addElementBuffer(EboPtr &ebo)
	{
		_ebo.reset(ebo.release());
		glBindVertexArray(_vao);
		_ebo->bind();
		glBindVertexArray(0);
		_ebo->unbind();
	}

	void VertexObject::draw() const
	{
		glBindVertexArray(_vao);
		glDrawElements(GL_TRIANGLES, _ebo->size(), GL_UNSIGNED_INT, nullptr);
		glBindVertexArray(0);
	}
}

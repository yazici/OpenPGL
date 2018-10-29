#include <cassert>
#include <stdexcept>

#include "renderer/VertexObject.h"

using namespace std;

namespace pgl
{
	VertexObject *VertexObject::create(const string_view &name)
	{
		VertexObject *vao = new VertexObject();
		vao->_name = name;
		return vao;
	}

	VertexObject::VertexObject() :
		_ebo(nullptr),
		_handle(0)
	{
		glGenVertexArrays(1, &_handle);
	}

	VertexObject::~VertexObject()
	{
		for (auto &vbo : _vertexBuffers){
			delete vbo.second;
		}

		glDeleteVertexArrays(1, &_handle);
	}

	void VertexObject::addVertexBuffer(const string &n, VertexBuffer *buffer)
	{
		if (!buffer) {
			throw invalid_argument("The buffer can't be a null pointer.");
		} else if (_vertexBuffers.find(n) != _vertexBuffers.end()) {
			throw invalid_argument("A buffer with this name has already been saved.");
		}

		_vertexBuffers[n] = buffer;
	}

	void VertexObject::addVertexBuffer(const string &n, VertexBuffer *buffer, const AttributeInfo &info)
	{
		if (_attribLocation.find(info.name) != _attribLocation.end()) {
			throw invalid_argument("A attribute with this name has already been saved.");
		}
		
		assert(_handle);
		addVertexBuffer(n, buffer);
		_attribLocation[info.name] = info.index;
		
		buffer->bind();
		glBindVertexArray(_handle);
		glVertexAttribPointer(info.index, info.size, info.type, info.normalized, info.stride, (const void *)info.pointer);
		glEnableVertexAttribArray(info.index);
		buffer->unbind();
	}
}

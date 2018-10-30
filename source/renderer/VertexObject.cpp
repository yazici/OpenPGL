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

		delete _ebo;

		glDeleteVertexArrays(1, &_handle);
	}

	void VertexObject::addIndexBuffer(IndexBuffer *ebo)
	{
		if (!ebo) {
			throw invalid_argument("The element buffer index can't be a null pointer.");
		}
		_ebo = ebo;
		glBindVertexArray(_handle);
		_ebo->bind();
		glBindVertexArray(0);
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

	void VertexObject::addAttributeInfo(const std::string &buffer, const AttributeInfo &attr)
	{
		auto buf = _vertexBuffers.find(buffer);

		if (buf == _vertexBuffers.end()) {
			throw invalid_argument("The buffer with this name is not saved.");
		} else if (_attribLocation.find(attr.name) != _attribLocation.end()) {
			throw invalid_argument("A attribute with this name has already been saved.");
		}

		_attribLocation[attr.name] = attr.index;
		buf->second->bind();
		glVertexAttribPointer(attr.index, attr.size, attr.type, attr.normalized, attr.stride, (const void *)attr.pointer);
		glEnableVertexAttribArray(attr.index);
		buf->second->unbind();
	}

	void VertexObject::draw(const ShaderProgram &sp) const
	{
		if (!_ebo) {
			throw invalid_argument("The element buffer index can't be a null pointer.");
		}

		sp.use();
		glBindVertexArray(_handle);
		glDrawElements(GL_TRIANGLES, _ebo->size(), GL_UNSIGNED_INT, nullptr);
		glBindVertexArray(0);
	}
}

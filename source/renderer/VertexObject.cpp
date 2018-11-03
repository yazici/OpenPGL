#include <cassert>
#include <stdexcept>

#include "renderer/VertexObject.h"

namespace pgl
{
	const AttributeInfo AttributeInfo::POSITION = { "position", 0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), 0 };
	const AttributeInfo AttributeInfo::NORMAL   = { "normal",   1, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), 0 };
	const AttributeInfo AttributeInfo::TEXCOORD = { "texCoord", 2, 2, GL_FLOAT, GL_FALSE, sizeof(vec2), 0 };
	const AttributeInfo AttributeInfo::COLOR    = { "color",    3, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), 0 };

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
		for (auto vbo : _vertexBuffers){
			delete vbo;
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


	inline void VertexObject::_addVertexBuffer(VertexBuffer *buffer)
	{
		if (!buffer) {
			throw invalid_argument("The buffer can't be a null pointer.");
		}

		_vertexBuffers.push_back(buffer);
	}

	void VertexObject::_addAttributeInfo(const AttributeInfo &attr)
	{
		auto iter = _attribLocation.find(attr.name);

		if (iter != _attribLocation.end()) {
			throw invalid_argument("This attribute has already been added in this vertex object.");
		}

		iter->second = attr.index;
		glVertexAttribPointer(attr.index, attr.size, attr.type, attr.normalized, attr.stride, (const void *)attr.pointer);
		glEnableVertexAttribArray(attr.index);
	}

	void VertexObject::addVertexBuffer(VertexBuffer *buffer, const AttributeInfo &attr1)
	{
		assert(_handle);

		_addVertexBuffer(buffer);
		buffer->bind();
		glBindVertexArray(_handle);

		_addAttributeInfo(attr1);

		buffer->unbind();
		glBindVertexArray(0);
	}

	void VertexObject::addVertexBuffer(VertexBuffer *buffer, const AttributeInfo &attr1, const AttributeInfo &attr2)
	{
		assert(_handle);

		_addVertexBuffer(buffer);
		buffer->bind();
		glBindVertexArray(_handle);

		_addAttributeInfo(attr1);
		_addAttributeInfo(attr2);


		buffer->unbind();
		glBindVertexArray(0);
	}

	void VertexObject::addVertexBuffer(VertexBuffer *buffer, const AttributeInfo &attr1, const AttributeInfo &attr2, 
		const AttributeInfo &attr3)
	{
		assert(_handle);

		_addVertexBuffer(buffer);
		buffer->bind();
		glBindVertexArray(_handle);

		_addAttributeInfo(attr1);
		_addAttributeInfo(attr2);
		_addAttributeInfo(attr3);

		buffer->unbind();
		glBindVertexArray(0);
	}

	void VertexObject::addVertexBuffer(VertexBuffer *buffer, const AttributeInfo &attr1, const AttributeInfo &attr2, 
		const AttributeInfo &attr3, const AttributeInfo &attr4)
	{
		assert(_handle);

		_addVertexBuffer(buffer);
		buffer->bind();
		glBindVertexArray(_handle);

		_addAttributeInfo(attr1);
		_addAttributeInfo(attr2);
		_addAttributeInfo(attr3);
		_addAttributeInfo(attr4);

		buffer->unbind();
		glBindVertexArray(0);
	}

	void VertexObject::addVertexBuffer(VertexBuffer *buffer, const vector<AttributeInfo> &attribs)
	{
		assert(_handle);

		_addVertexBuffer(buffer);
		buffer->bind();
		glBindVertexArray(_handle);

		for (auto &attr : attribs) {
			_addAttributeInfo(attr);
		}

		buffer->unbind();
		glBindVertexArray(0);
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

	void VertexObject::draw() const
	{
		if (!_ebo) {
			throw invalid_argument("The element buffer index can't be a null pointer.");
		}

		glBindVertexArray(_handle);
		glDrawElements(GL_TRIANGLES, _ebo->size(), GL_UNSIGNED_INT, nullptr);
		glBindVertexArray(0);
	}
}

#include "renderer/VertexObject.h"

namespace pgl
{
	VertexObject * VertexObject::create(const std::string_view & name)
	{
		return new VertexObject();
	}

	VertexObject::VertexObject() :
		_ebo(nullptr),
		_handle(0)
	{
	}

	VertexObject::~VertexObject()
	{
		for (auto &vbo : _vertexBuffers){
			delete vbo.second;
		}

		glDeleteVertexArrays(1, &_handle);
	}
}

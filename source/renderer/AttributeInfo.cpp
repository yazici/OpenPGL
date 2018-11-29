#include <stdexcept>
#include <utility>
#include <GL/glew.h>

#include "renderer/AttributeInfo.h"

namespace pgl
{
	AttributeInfo AttributeInfo::POSITION = {0, 3, GL_FLOAT, GL_FALSE, 0};
	AttributeInfo AttributeInfo::NORMAL   = {1, 3, GL_FLOAT, GL_FALSE, 0};
	AttributeInfo AttributeInfo::TEXCOORD = {2, 2, GL_FLOAT, GL_FALSE, 0};

	AttributeLayout::AttributeLayout()
		: _stride(0)
	{
	}
	
	AttributeLayout::AttributeLayout(const AttributeLayout &a)
		: _attribs(a._attribs),
		  _stride(a._stride)
	{
	}

	AttributeLayout::AttributeLayout(AttributeLayout &&a)
		: _stride(0)
	{
		std::swap(_attribs, a._attribs);
		std::swap(_stride, a._stride);
	}

	AttributeLayout::~AttributeLayout()
	{
	}

	void AttributeLayout::push(const AttributeInfo &a)
	{
		unsigned int p = _stride;

		switch (a.type)
		{
		case GL_FLOAT:
			_stride += sizeof(GLfloat) * a.size;
			break;
		case GL_INT:
			_stride += sizeof(GLint) * a.size;
			break;
		case GL_UNSIGNED_INT:
			_stride += sizeof(GLuint) * a.size;
			break;
		case GL_BYTE:
			_stride += sizeof(GLbyte) * a.size;
			break;
		case GL_UNSIGNED_BYTE:
			_stride += sizeof(GLubyte) * a.size;
			break;
		case GL_SHORT:
			_stride += sizeof(GLshort) * a.size;
			break;
		case GL_UNSIGNED_SHORT:
			_stride += sizeof(GLushort) * a.size;
			break;
		default:
			throw std::invalid_argument("Invalid attribute type.");
			break;
		}

		_attribs.push_back(a);
		_attribs.back().pointer = p;
	}

	const AttributeInfo &AttributeLayout::get(size_t i) const
	{
		if (length() <= i) {
			throw std::invalid_argument("Index out of range.");
		}

		return _attribs[i];
	}

	unsigned int AttributeLayout::stride() const
	{
		return _stride;
	}

	size_t AttributeLayout::length() const
	{
		return _attribs.size();
	}

	AttributeLayout &AttributeLayout::operator|(const AttributeInfo &a)
	{
		push(a);
		return *this;
	}

	AttributeLayout operator|(const AttributeInfo &a1, const AttributeInfo &a2)
	{
		AttributeLayout l;
		l.push(a1);
		l.push(a2);
		return l;
	}

	AttributeInfo::operator AttributeLayout() const
	{
		AttributeLayout l;
		l.push(*this);
		return l;
	}
}

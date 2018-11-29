#ifndef _RENDERER_VERTEXOBJECT_H
#define _RENDERER_VERTEXOBJECT_H

#include <vector>
#include <memory>
#include <GL/glew.h>

#include "renderer/VertexBuffer.h"
#include "renderer/ElementBuffer.h"
#include "renderer/AttributeInfo.h"

namespace pgl
{
	class VertexObject;
	typedef std::unique_ptr<VertexObject> VaoPtr;

	class VertexObject
	{
	public:

		static VaoPtr create();

		~VertexObject();

		void addVertexBuffer(VboPtr &buffer, const AttributeLayout &attribs);

		void addElementBuffer(EboPtr &ebo);

		void draw() const;

	private:
		
		VertexObject();

		VertexObject(const VertexObject &o) = delete;

	private:

		std::vector<VboPtr> _buffers;
		EboPtr _ebo;
		unsigned int _vao;
	};
}

#endif

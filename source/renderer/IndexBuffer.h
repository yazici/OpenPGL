#ifndef _RENDERER_INDEXBUFFER_H
#define _RENDERER_INDEXBUFFER_H

#include <vector>
#include <GL/glew.h>

namespace pgl
{
	using std::vector;

    class IndexBuffer
    {
	public:
		IndexBuffer();
		
		IndexBuffer(const vector<GLuint> &indx);
		
		IndexBuffer(const GLuint *indx, size_t size);

		IndexBuffer(const IndexBuffer &i) = delete;

		~IndexBuffer();

		void create(const vector<GLuint> &indx);

		void create(const GLuint *indx, size_t size);

		void bind() const noexcept;

		void unbind() const noexcept;

		size_t size() const noexcept;

	private:
		GLuint _ebo;
		size_t _countIndices;
    };
}

#endif // !_RENDERER_INDEXBUFFER_H

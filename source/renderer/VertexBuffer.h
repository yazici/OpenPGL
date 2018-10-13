#ifndef _RENDERER_VERTEXBUFFER_H
#define _RENDERER_VERTEXBUFFER_H

#include <GL/glew.h>

namespace pgl
{
    class Mesh;

    class VertexBuffer
    {
    public:
        
		static VertexBuffer *create(size_t size, GLenum usage = GL_STATIC_DRAW, const void *data = nullptr);

        ~VertexBuffer();
		
		void newData(size_t size, GLenum usage = GL_STATIC_DRAW, const void *data = nullptr);

		void updateData(size_t offset, size_t size, const void *data);
			
        void bind() const noexcept;

        void unbind() const noexcept;

	private:

		VertexBuffer();

		VertexBuffer(const VertexBuffer &v) = delete;

    private:
        GLuint _handle;
		size_t _size;
    };
}

#endif //!_RENDERER_VERTEXBUFFER_H

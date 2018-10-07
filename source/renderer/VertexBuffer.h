#ifndef _RENDERER_VERTEXBUFFER_H
#define _RENDERER_VERTEXBUFFER_H

#include <GL/glew.h>

namespace pgl
{
    class Mesh;

    class VertexBuffer
    {
    public:
        
        VertexBuffer();

        VertexBuffer(size_t size, const void *data);
    
		VertexBuffer(const VertexBuffer &v) = delete;

        ~VertexBuffer();

        void create(size_t size, const void *data);

        void bind() const noexcept;

        void unbind() const noexcept;

    private:
        GLuint _vbo;
    };
}

#endif //!_RENDERER_VERTEXBUFFER_H

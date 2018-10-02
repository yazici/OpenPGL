#ifndef _RENDERER_VERTEXBUFFER_H
#define _RENDERER_VERTEXBUFFER_H

#include <stdint.h>
#include <GL/glew.h>

namespace pgl
{
    class Mesh;

    class VertexBuffer
    {
    public:
        
        VertexBuffer();

        VertexBuffer(size_t size, const void *data);
    
        ~VertexBuffer();

        void Create(size_t size, const void *data);

        void Bind() noexcept;

        void UnBind() noexcept;

    private:
        uint32_t _vbo;
    };
}

#endif //!_RENDERER_VERTEXBUFFER_H

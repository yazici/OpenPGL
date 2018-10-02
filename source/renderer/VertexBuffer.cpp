#include <stdexcept>
#include <GL/glew.h>

#include "VertexBuffer.h"

namespace pgl
{
    VertexBuffer::VertexBuffer() : _vbo(0u)
    {
    }

    VertexBuffer::VertexBuffer(size_t size, const void * data) : VertexBuffer()
    {
        Create(size, data);
    }

    VertexBuffer::~VertexBuffer()
    {
        glDeleteBuffers(1, &_vbo);
    }

    void VertexBuffer::Create(size_t size, const void * data)
    {
        if (_vbo) {
            throw std::runtime_error("The vertex buffer object has been created and can't be created again.");
        }

        if (nullptr == data) {
            throw std::invalid_argument("You passed in a null pointer. The 'data' argument can't be a null pointer.");
        }

        glGenBuffers(1, &_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

        int loadSize = 0;
        glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &loadSize);

        if ((size_t)loadSize != size) {
            glDeleteBuffers(1, &_vbo);
            // FIXME: ��������� ���������� ��������� �� ������.
            throw std::runtime_error("OpenGL buffer size error. WTF?");
        }

        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void VertexBuffer::Bind() noexcept
    {
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    }

    void VertexBuffer::UnBind() noexcept
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}
#ifndef _RENDERER_VAO_H
#define _RENDERER_VAO_H

#include <stdint.h>
#include <vector>

#include "IndexBuffer.h"
#include "VertexBuffer.h"

namespace pgl
{
    using std::vector;

    class Mesh;

    class VertexObject
    {
    public:

        /**
        * ������� OpenGL ������, ������� ��������� ������ ������ � ������������ ��� ������� ���� 
        * ������.
        * 
        * @param mesh ����������� ��� ������� ���.
        */
        VertexObject(const Mesh &mesh);

        /**
        * ����������� ���������� ������� � ��� ����� � ����������� ��� ������ ������� OpenGL 
        * ������ ������.
        */
        ~VertexObject();

        /**
        * ���������� ��������� �� ��������� ������� (VBO). ����������� ����� �����������, ���� 
        * VAO ��������� � �������� ��������� (�.�. IsEnable() ���������� true).
        */
        void Draw() const;
        //void Draw(const Shader &shader);

        /**
        * ���������� ������� VAO.
        */
        void Enable() const;

        /**
        * ��������� ������� VAO.
        */
        void Disable() const;

        /** 
        * ��������� ����������� �� VAO.
        * 
        * @return true, ���� VAO �����������, false � ��������� ������.
        */
        bool IsEnable() const;

    private:
        vector<VertexBuffer> _vbos;
        IndexBuffer _indices;
        uint32_t _vao;
        bool _enable;
    };
}

#endif // !_RENDERER_VAO_H

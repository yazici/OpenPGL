#ifndef _DATA_MESH_H
#define _DATA_MESH_H

#include <stdint.h>
#include <glm/glm.hpp>

namespace pgl
{
    using glm::vec3;
    using glm::ivec2;

    class Mesh
    {
    public:
        
        /**
        * ����������� � ��������� ����������� ��� �������� ����.
        * @param cVertices ���������� ������
        * @param cTriangles ���������� ����������� ��������� � ����
        * @throws std::invalid_argument � ������, ���� ���� �� ���� �� ���������� ������ ��� ����� 0
        */
        Mesh(size_t cVertices, size_t cTriangles);

        /**
        * ����������� �����������.
        * @param m ���������� ���
        */
        Mesh(const Mesh &m);

        ~Mesh();

        /**
        * ������� ��� ����������������� ������.
        */
        vec3 &vertex(size_t i);
        vec3 &normal(size_t i);
        ivec2 &uv(size_t i);
        uint32_t &triangle(size_t i);
        
        /**
        * ������� ��� ����������������� ������.
        */
        const vec3 &vertex(size_t i) const;
        const vec3 &normal(size_t i) const;
        const ivec2 &uv(size_t i) const;
        uint32_t triangle(size_t i) const;

        /**
        * ������� ��� ��������� �������� ������.
        */
        const vec3 *vertices() const;
        const vec3 *normals() const;
        const ivec2 *uv() const;
        const uint32_t *triangles() const;

    private:
        vec3 *_vertices;
        vec3 *_normals;
        ivec2 *_uv;
        uint32_t *_triangles;
        size_t _cVertices;
        size_t _cTriangles;
    };
}

#endif

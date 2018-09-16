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
        * Конструктор с заданными параметрами для создания меша.
        * @param cVertices количество вершин
        * @param cTriangles количество треугольных полигонов в меше
        * @throws std::invalid_argument в случае, если хотя бы один из аргументов меньше или равен 0
        */
        Mesh(size_t cVertices, size_t cTriangles);

        /**
        * Конструктор копирования.
        * @param m копируемый меш
        */
        Mesh(const Mesh &m);

        ~Mesh();

        /**
        * Сеттеры для инкапсулированных данных.
        */
        vec3 &vertex(size_t i);
        vec3 &normal(size_t i);
        ivec2 &uv(size_t i);
        uint32_t &triangle(size_t i);
        
        /**
        * Геттеры для инкапсулированных данных.
        */
        const vec3 &vertex(size_t i) const;
        const vec3 &normal(size_t i) const;
        const ivec2 &uv(size_t i) const;
        uint32_t triangle(size_t i) const;

        /**
        * Геттеры для получения массивов данных.
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

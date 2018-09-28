#ifndef _DATA_MESH_H
#define _DATA_MESH_H

#include <stdint.h>
#include <glm/glm.hpp>

namespace pgl
{
    using glm::vec3;
    using glm::vec2;

    class Mesh
    {
    public:
        
        /**
        * Создает квадратную плоскость со стороной planeSize.
        *
        * @param divisions разрещение плоскости в полигонах
        * @param planeSize размер одного полигона
        * @return возвращает созданный меш
        */
        static Mesh CreatePlane(size_t divisions, float planeSize);

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


        /**
        * Конструктор перемещения.
        * @param m перемещаемый меш
        */
        Mesh(Mesh &&m);

        ~Mesh();

        /**
        * Сеттеры для инкапсулированных данных.
        */
        vec3 &vertex(size_t i);
        vec3 &normal(size_t i);
        vec2 &uv(size_t i);
        uint32_t &triangle(size_t i);
        
        /**
        * Геттеры для инкапсулированных данных.
        */
        const vec3 &vertex(size_t i) const;
        const vec3 &normal(size_t i) const;
        const vec2 &uv(size_t i) const;
        uint32_t triangle(size_t i) const;

        /**
        * Геттеры для получения массивов данных.
        */
        const vec3 *vertices() const;
        const vec3 *normals() const;
        const vec2 *uv() const;
        const uint32_t *triangles() const;

        // TODO: operator = (const &)
        // TODO: operator = (const &&)
    private:
        vec3 *_vertices;
        vec3 *_normals;
        vec2 *_uv;
        uint32_t *_triangles;
        size_t _cVertices;
        size_t _cTriangles;
    };
}

#endif

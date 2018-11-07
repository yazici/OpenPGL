#ifndef _DATA_MESH_H
#define _DATA_MESH_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

namespace pgl
{
    using glm::vec3;
    using glm::vec2;
    using std::vector;

    class Mesh
    {
    public:
        
        /**
        * Создает плоскость со сторонами w и h.
        *
        * @param w ширина плоскости в полигонах.
        * @param h высота плоскости в полигонах.
        * @param divisionSize размер квадратного полигона.
        * @return возвращает созданный меш.
        */
		static Mesh createPlane(int w, int h, float divisionSize);

        /**
        * Конструктор с заданными параметрами для создания меша.
        * @param cVertices количество вершин.
        * @param cTriangles количество треугольных полигонов в меше.
        * @throws std::invalid_argument в случае, если хотя бы один из аргументов меньше или равен 0.
        */
        Mesh(int cVertices, int cTriangles);

        /**
        * Конструктор копирования.
        * @param m копируемый меш.
        */
        Mesh(const Mesh &m);

        /**
        * Конструктор перемещения.
        * @param m перемещаемый меш.
        */
        Mesh(Mesh &&m);

        ~Mesh();

        /**
        * Сеттеры для инкапсулированных данных.
        * @param i индекс данных.
        */
        vec3 &vertex(int i);
        vec3 &normal(int i);
        vec2 &uv(int i);
        GLuint &triangle(int i);
        
        /**
        * Геттеры для инкапсулированных данных.
        * @param i индекс данных.
        */
        const vec3 &vertex(int i) const;
        const vec3 &normal(int i) const;
        const vec2 &uv(int i) const;
        GLuint triangle(int i) const;

        /**
        * Геттеры для получения массивов данных.
        */
        const vector<vec3> &vertices() const;
        const vector<vec3> &normals() const;
        const vector<vec2> &uvs() const;
        const vector<GLuint> &triangles() const;

        // TODO: operator = (const &)
        Mesh &operator =(const Mesh &m);
        // TODO: operator = (const &&)
        Mesh &operator =(const Mesh &&m);
    private:
        vector<vec3> _vertices;
        vector<vec3> _normals;
        vector<vec2> _uv;
        vector<GLuint> _triangles;
    };
}

#endif

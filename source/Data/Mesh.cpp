#include <stdexcept>
#include <utility>

#include "Mesh.h"

namespace pgl
{
    Mesh::Mesh(size_t cVertices, size_t cTriangles) :
        _cVertices(cVertices),
        _cTriangles(cTriangles)
    {
        if (0 >= _cVertices) {
            throw std::invalid_argument("The argument cVertices must be greater than 0.");
        }
        else if (0 >= _cTriangles) {
            throw std::invalid_argument("The argument cTrianlges must be greater than 0.");
        }

        // TODO: обработать случай при котором память выделить невозможно. Исключение std::bad_alloc() или nullptr.
        _vertices = new vec3[_cVertices];
        _normals = new vec3[_cVertices];
        _uv = new ivec2[_cVertices];
        _triangles = new uint32_t[_cTriangles];
    }

    Mesh::Mesh(const Mesh & m) :
        Mesh(m._cVertices, m._cTriangles)
    {
        // Для выполнения в Visual Studio требуется отключение предупреждения C4996.
        std::copy(m._vertices, m._vertices + m._cVertices, _vertices);
        std::copy(m._normals, m._normals + m._cVertices, _normals);
        std::copy(m._uv, m._uv + m._cVertices, _uv);
        std::copy(m._triangles, m._triangles + m._cVertices, _triangles);
    }

    Mesh::~Mesh()
    {
        delete[] _vertices;
        delete[] _normals;
        delete[] _uv;
        delete[] _triangles;
    }

    /**
    * Сеттеры для инкапсулированных данных.
    */
    vec3 & Mesh::vertex(size_t i)
    {
        return _vertices[i];
    }

    vec3 & Mesh::normal(size_t i)
    {
        return _normals[i];
    }

    ivec2 & Mesh::uv(size_t i)
    {
        return _uv[i];
    }

    uint32_t & Mesh::triangle(size_t i)
    {
        return _triangles[i];
    }

    /**
    * Геттеры для инкапсулированных данных.
    */
    const vec3 & Mesh::vertex(size_t i) const
    {
        return _vertices[i];
    }

    const vec3 & Mesh::normal(size_t i) const
    {
        return _normals[i];
    }

    const ivec2 & Mesh::uv(size_t i) const
    {
        return _uv[i];
    }

    uint32_t Mesh::triangle(size_t i) const
    {
        return _triangles[i];
    }

    /**
    * Геттеры для получения массивов данных.
    */
    const vec3 * Mesh::vertices() const
    {
        return _vertices;
    }

    const vec3 * Mesh::normals() const
    {
        return _normals;
    }

    const ivec2 * Mesh::uv() const
    {
        return _uv;
    }

    const uint32_t * Mesh::triangles() const
    {
        return _triangles;
    }
}

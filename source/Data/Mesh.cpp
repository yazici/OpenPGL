#include <stdexcept>
#include <utility>

#include "Mesh.h"

namespace pgl
{
    Mesh Mesh::CreatePlane(size_t divisions, float planeSize)
    {
        size_t size = divisions + 1;
        size_t cVert = size * size;
        size_t cTriangl = divisions * divisions * 6u;
        Mesh plane(cVert, cTriangl);

        float halfPlaneSize = 0.5f * planeSize;
        float divisionSize = planeSize / divisions;
        size_t triangleOff = 0;

        for (size_t y = 0; y < size; ++y) {
            vec3 *vLine = plane._vertices + y * size;
            vec3 *nLine = plane._normals + y * size;
            vec2 *uvLine = plane._uv + y * size;

            for (size_t x = 0; x < size; ++x) {
                // vLine[x] = vec3(x * divisionSize - halfPlaneSize, 0.0, y * divisionSize - halfPlaneSize);
                vLine[x].x = x * divisionSize - halfPlaneSize;
                vLine[x].y = 0.0;
                vLine[x].z = y * divisionSize - halfPlaneSize;

                nLine[x] = vec3(0.0f, 1.0f, 0.0f);
                uvLine[x] = vec2((float)x / divisions, 1.0f - y / divisions);

                if (x < divisions && y < divisions) {
                    int tLeft  = y * size + x;
                    int bLeft = (y + 1) * size + x;
                    // Правый верхний треугольник.
                    plane._triangles[triangleOff   ]  = tLeft;
                    plane._triangles[triangleOff + 1] = tLeft + 1;
                    plane._triangles[triangleOff + 2] = bLeft + 1;
                    // Левый нижний треугольник.
                    plane._triangles[triangleOff + 3] = tLeft;
                    plane._triangles[triangleOff + 4] = bLeft + 1;
                    plane._triangles[triangleOff + 5] = bLeft;
                    triangleOff += 6;
                }
            }
        }

        return std::move(plane);
    }

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
        _vertices  = new vec3[_cVertices];
        _normals   = new vec3[_cVertices];
        _uv        = new vec2[_cVertices];
        _triangles = new uint32_t[_cTriangles];
    }

    Mesh::Mesh(const Mesh &m) :
        Mesh(m._cVertices, m._cTriangles)
    {
        // Для выполнения в Visual Studio требуется отключение предупреждения C4996.
        std::copy(m._vertices, m._vertices + m._cVertices, _vertices);
        std::copy(m._normals, m._normals + m._cVertices, _normals);
        std::copy(m._uv, m._uv + m._cVertices, _uv);
        std::copy(m._triangles, m._triangles + m._cVertices, _triangles);
    }

    Mesh::Mesh(Mesh &&m)
    {
        _cVertices  = m._cVertices;
        _cTriangles = m._cTriangles;
        m._cVertices  = 0u;
        m._cTriangles = 0u;

        _vertices  = m._vertices;
        _normals   = m._normals;
        _uv        = m._uv;
        _triangles = m._triangles;

        m._vertices  = nullptr;
        m._normals   = nullptr;
        m._uv        = nullptr;
        m._triangles = nullptr;
    }

    Mesh::~Mesh()
    {
        if (_cVertices) {
            delete[] _vertices;
            delete[] _normals;
            delete[] _uv;
        }

        if (_cTriangles) {
            delete[] _triangles;
        }
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

    vec2 & Mesh::uv(size_t i)
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

    const vec2 & Mesh::uv(size_t i) const
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

    const vec2 * Mesh::uv() const
    {
        return _uv;
    }

    const uint32_t * Mesh::triangles() const
    {
        return _triangles;
    }
}

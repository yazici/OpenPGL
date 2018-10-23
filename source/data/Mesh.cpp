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
            size_t line = y * size;

            for (size_t x = 0; x < size; ++x) {
                plane._vertices[line + x] = vec3(x * divisionSize - halfPlaneSize,
                                                 0.0,
                                                 y * divisionSize - halfPlaneSize);

                plane._normals[line + x] = vec3(0.0f, 1.0f, 0.0f);
                plane._uv[line + x] = vec2((float)x / divisions, 1.0f - y / divisions);

                if (x < divisions && y < divisions) {
                    GLuint tLeft = (GLuint)(y * size + x);
                    GLuint bLeft = (GLuint)((y + 1) * size + x);
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

    Mesh::Mesh(size_t cVertices, size_t cTriangles)
    {
        if (0 >= cVertices) {
            throw std::invalid_argument("The argument cVertices must be greater than 0.");
        }
        else if (0 >= cTriangles) {
            throw std::invalid_argument("The argument cTrianlges must be greater than 0.");
        }

        _vertices.resize(cVertices, vec3(0.0f));
        _normals.resize(cVertices, vec3(0.0f));
        _uv.resize(cVertices, vec2(0.0f));
        _triangles.resize(cTriangles, 0u);
    }

    Mesh::Mesh(const Mesh &m) 
    {
        _vertices  = m._vertices;
        _normals   = m._normals;
        _uv        = m._uv;
        _triangles = m._triangles;
        
    }

    Mesh::Mesh(Mesh &&m)
    {
        _vertices  = std::move(m._vertices);
        _normals   = std::move(m._normals);
        _uv        = std::move(m._uv);
        _triangles = std::move(m._triangles);
    }

    Mesh::~Mesh()
    {
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

    GLuint & Mesh::triangle(size_t i)
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

    GLuint Mesh::triangle(size_t i) const
    {
        return _triangles[i];
    }

    /**
    * Геттеры для получения массивов данных.
    */
    const vector<vec3> &Mesh::vertices() const
    {
        return _vertices;
    }

    const vector<vec3> &Mesh::normals() const
    {
        return _normals;
    }

    const vector<vec2> &Mesh::uvs() const
    {
        return _uv;
    }

    const vector<GLuint> &Mesh::triangles() const
    {
        return _triangles;
    }

    Mesh &Mesh::operator =(const Mesh &m)
    {
        if (&m != this) {
            _vertices  = m._vertices;
            _normals   = m._normals;
            _uv        = m._uv;
            _triangles = m._triangles;
        }

        return *this;
    }

    Mesh &Mesh::operator =(const Mesh &&m)
    {
        if (&m != this) {
            _vertices  = std::move(m._vertices);
            _normals   = std::move(m._normals);
            _uv        = std::move(m._uv);
            _triangles = std::move(m._triangles);    
        }

        return *this;
    }
}

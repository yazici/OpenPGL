#include <stdexcept>
#include <utility>

#include "Mesh.h"

namespace pgl
{
	Mesh Mesh::createPlane(int w, int h, float divisionSize)
	{
		int countVertex = (w + 1) * (h + 1);
		int countIndex = 6 * w * h;
		Mesh p(countVertex, countIndex);

		float startX = 0.5f * w * divisionSize;
		float startY = 0.5f * h * divisionSize;
		int triangleOff = 0;

		for (int y = 0; y <= h; ++y) {
			int line = y * (w + 1);

			for (int x = 0; x <= w; ++x) {
				p._vertices[line + x] = vec3(x * divisionSize - startX, 0.0f, y * divisionSize - startY);
				p._normals[line + x] = vec3(0.0f, 1.0f, 0.0f);
				p._uv[line + x] = vec2((float)x / w, 1.0f - (float)y / h);

				if (x < w && y < h) {
					GLuint tLeft = (GLuint)(y * (w + 1) + x);
					GLuint bLeft = (GLuint)((y + 1) * (w + 1) + x);
					// Правый верхний треугольник.
					p._triangles[triangleOff] = bLeft;
					p._triangles[triangleOff + 1] = tLeft + 1;
					p._triangles[triangleOff + 2] = tLeft;
					// Левый нижний треугольник.
					p._triangles[triangleOff + 3] = bLeft;
					p._triangles[triangleOff + 4] = bLeft + 1;
					p._triangles[triangleOff + 5] = tLeft + 1;
					triangleOff += 6;
				}
			}
		}

		return p;
	}

    Mesh::Mesh(int cVertices, int cTriangles)
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
    vec3 & Mesh::vertex(int i)
    {
        return _vertices[i];
    }

    vec3 & Mesh::normal(int i)
    {
        return _normals[i];
    }

    vec2 & Mesh::uv(int i)
    {
        return _uv[i];
    }

	GLuint & Mesh::triangle(int i)
    {
        return _triangles[i];
    }

    /**
    * Геттеры для инкапсулированных данных.
    */
    const vec3 & Mesh::vertex(int i) const
    {
        return _vertices[i];
    }

    const vec3 & Mesh::normal(int i) const
    {
        return _normals[i];
    }

    const vec2 & Mesh::uv(int i) const
    {
        return _uv[i];
    }

    GLuint Mesh::triangle(int i) const
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

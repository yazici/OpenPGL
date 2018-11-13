#include <stdexcept>
#include <utility>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/normal.hpp>

#include "data/Mesh.h"

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
					// Правый нижний треугольник.
					p._triangles[triangleOff    ] = bLeft;
					p._triangles[triangleOff + 1] = bLeft + 1;
					p._triangles[triangleOff + 2] = tLeft + 1;
					// Левый верхний треугольник.
					p._triangles[triangleOff + 3] = tLeft + 1;
					p._triangles[triangleOff + 4] = tLeft;
					p._triangles[triangleOff + 5] = bLeft;
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

	void Mesh::calculateNormal()
	{
		int size = _triangles.size();

		for (int i = 0; i < size; i += 3) {
			vec3 &p1 = _vertices[_triangles[i    ]];
			vec3 &p2 = _vertices[_triangles[i + 1]];
			vec3 &p3 = _vertices[_triangles[i + 2]];
			vec3 n = triangleNormal(p1, p2, p3);

			_normals[_triangles[i    ]] += n;
			_normals[_triangles[i + 1]] += n;
			_normals[_triangles[i + 2]] += n;
		}
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

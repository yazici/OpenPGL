#ifndef _RENDERER_SHADERPROGRAM_H
#define _RENDERER_SHADERPROGRAM_H

#include <GL/glew.h>
#include <string>
#include <glm/glm.hpp>

#include "Shader.h"

using namespace std;
using namespace glm;

namespace pgl
{
	class ShaderProgram
	{
	public:
		
		ShaderProgram(const string_view &vert, const string_view &frag);

		/**
		* Устанавливает шейдерную программу, как часть текущего рендера.
		*/
		void use() const noexcept;

		/**
		* Возвращает индекс шейдерного аттрибута с именем name.
		* @param name имя шейдерного аттрибута.
		* @return индекс шейдерного аттрибута.
		*/
		int attributeLocation(const string_view &name) const noexcept;

		/**
		* Возвращает индекс uniform-переменной с именем name.
		* @param name имя uniform-переменной.
		* @return индекс.
		*/
		int uniformLocation(const string_view &name) const noexcept;
		
		/**
		* Методы устанавливают значение uniform-переменной для текущей шейдерной программы.
		* @param loc индекс переменной.
		* @param v значение переменной.
		*/
		void uniform(int loc, int   v);
		void uniform(int loc, float v);
		void uniform(int loc, const vec2  &v);
		void uniform(int loc, const ivec2 &v);
		void uniform(int loc, const vec3  &v);
		void uniform(int loc, const ivec3 &v);
		void uniform(int loc, const vec4  &v);
		void uniform(int loc, const ivec4 &v);

		/**
		* Методы устанавливают значение uniform-переменной для текущей шейдерной программы.
		* @param name имя переменной.
		* @param v значение переменной.
		*/
		void uniform(const string_view &name, int   v);
		void uniform(const string_view &name, float v);
		void uniform(const string_view &name, const vec2  &v);
		void uniform(const string_view &name, const ivec2 &v);
		void uniform(const string_view &name, const vec3  &v);
		void uniform(const string_view &name, const ivec3 &v);
		void uniform(const string_view &name, const vec4  &v);
		void uniform(const string_view &name, const ivec4 &v);

		/**
		* Методы устанавливают значение uniform-матрицы для текущей шейдерной программы.
		* @param name имя матрицы.
		* @param v матрица.
		*/
		void uniform(const string_view &name, const mat3 &v);
		void uniform(const string_view &name, const mat4 &v);

	private:
		Shader _vertex;
		Shader _fragment;
		GLuint _handle;
	};
}

#endif // !_RENDERER_SHADERPROGRAM_H

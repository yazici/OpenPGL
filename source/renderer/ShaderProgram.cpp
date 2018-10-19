#include <stdexcept>
#include <cassert>
#include <glm/gtc/type_ptr.hpp>

#include "ShaderProgram.h"

namespace pgl
{
	ShaderProgram::ShaderProgram(const string_view &vert, const string_view &frag) :
		_vertex(VERTEX, vert),
		_fragment(FRAGMENT, frag),
		_handle(0)
	{
		_handle = glCreateProgram();

		if (!_handle) {
			throw runtime_error("OpenGL can't create a shader programm.");
		}

		glAttachShader(_handle, _vertex._handle);
		glAttachShader(_handle, _fragment._handle);
		glLinkProgram(_handle);

		int status = 0;
		glGetProgramiv(_handle, GL_LINK_STATUS, &status);
		
		if (status) {
			glGetProgramiv(_handle, GL_INFO_LOG_LENGTH, &status);
			string log(status, '\0');
			glGetProgramInfoLog(_handle, status, nullptr, &log[0]);
			throw runtime_error(log);
		}
	}

	/**
	* Устанавливает шейдерную программу, как часть текущего рендера.
	*/
	void ShaderProgram::use() const noexcept
	{
		assert(_handle);
		glUseProgram(_handle);
	}

	/**
	* Возвращает индекс шейдерного аттрибута с именем name.
	* @param name имя шейдерного аттрибута.
	* @return индекс шейдерного аттрибута.
	*/
	int ShaderProgram::attributeLocation(const string_view &name) const noexcept
	{
		assert(_handle);
		return glGetAttribLocation(_handle, name.data());
	}

	/**
	* Возвращает индекс uniform-переменной с именем name.
	* @param name имя uniform-переменной.
	* @return индекс.
	*/
	int ShaderProgram::uniformLocation(const string_view &name) const noexcept
	{
		assert(_handle);
		return glGetUniformLocation(_handle, name.data());
	}

	/**
	* Методы устанавливают значение uniform-переменной для текущей шейдерной программы.
	* @param loc индекс переменной.
	* @param v значение переменной.
	*/
	void ShaderProgram::uniform(int loc, int v)
	{
		assert(_handle);
		glUniform1i(loc, v);
	}

	void ShaderProgram::uniform(int loc, float v)
	{
		assert(_handle);
		glUniform1f(loc, v);
	}

	void ShaderProgram::uniform(int loc, const vec2 &v)
	{
		assert(_handle);
		glUniform2fv(loc, 1, &v.x);
	}

	void ShaderProgram::uniform(int loc, const ivec2 &v)
	{
		assert(_handle);
		glUniform2iv(loc, 1, &v.x);
	}
	void ShaderProgram::uniform(int loc, const vec3 &v)
	{
		assert(_handle);
		glUniform3fv(loc, 1, &v.x);
	}

	void ShaderProgram::uniform(int loc, const ivec3 &v)
	{
		assert(_handle);
		glUniform3iv(loc, 1, &v.x);
	}

	void ShaderProgram::uniform(int loc, const vec4 &v)
	{
		assert(_handle);
		glUniform4fv(loc, 1, &v.x);
	}

	void ShaderProgram::uniform(int loc, const ivec4 &v)
	{
		assert(_handle);
		glUniform4iv(loc, 1, &v.x);
	}


	/**
	* Методы устанавливают значение uniform-переменной для текущей шейдерной программы.
	* @param name имя переменной.
	* @param v значение переменной.
	*/
	void ShaderProgram::uniform(const string_view &name, int v)
	{
		uniform(uniformLocation(name), v);
	}
	
	void ShaderProgram::uniform(const string_view &name, float v)
	{
		uniform(uniformLocation(name), v);
	}
	
	void ShaderProgram::uniform(const string_view &name, const vec2 &v)
	{
		uniform(uniformLocation(name), v);
	}
	
	void ShaderProgram::uniform(const string_view &name, const ivec2 &v)
	{
		uniform(uniformLocation(name), v);
	}
	
	void ShaderProgram::uniform(const string_view &name, const vec3 &v)
	{
		uniform(uniformLocation(name), v);
	}
	
	void ShaderProgram::uniform(const string_view &name, const ivec3 &v)
	{
		uniform(uniformLocation(name), v);
	}
	
	void ShaderProgram::uniform(const string_view &name, const vec4 &v)
	{
		uniform(uniformLocation(name), v);
	}
	
	void ShaderProgram::uniform(const string_view &name, const ivec4 &v)
	{
		uniform(uniformLocation(name), v);
	}

	/**
	* Методы устанавливают значение uniform-матрицы для текущей шейдерной программы.
	* @param name имя матрицы.
	* @param v матрица.
	*/
	void ShaderProgram::uniform(const string_view & name, const mat3 & v)
	{
		assert(_handle);
		int loc = uniformLocation(name);
		glUniformMatrix3fv(loc, 1, GL_FALSE, value_ptr(v));
	}

	void ShaderProgram::uniform(const string_view & name, const mat4 & v)
	{
		assert(_handle);
		int loc = uniformLocation(name);
		glUniformMatrix3fv(loc, 1, GL_FALSE, value_ptr(v));
	}
}

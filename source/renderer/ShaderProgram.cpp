#include <cassert>
#include <stdexcept>
#include <sstream>
#include <glm/gtc/type_ptr.hpp>

#include <renderer/ShaderProgram.h>

namespace pgl 
{
	using namespace std;
	using namespace glm;

	/**
	* Создает шейдерную программу.
	* @param vert путь к файлу с вершинным шейдером.
	* @param frag путь к файлу с фрагментным шейдером.
	*/
	ShaderProgram::ShaderProgram(const string_view &vert, const string_view &frag)
		: _vertex(VERTEX, vert),
		  _fragment(FRAGMENT, frag)
	{
		_program = glCreateProgram();

		if (!_program) {
			throw runtime_error("Program can't be created. OpenGL can't allocate resources.");
		}

		glAttachShader(_program, _vertex._shader);
		glAttachShader(_program, _fragment._shader);
		glLinkProgram(_program);
		auto e = getError();

		if (e) {
			stringstream msg;
			msg << "Program can't be linked. Log: " << e.value();
			throw runtime_error(msg.str());
		}
	}

	/**
	* Очищает выделенные ресурсы.
	*/
	ShaderProgram::~ShaderProgram()
	{
		glDeleteProgram(_program);
	}

	/**
	* Устанавливает шейдерную программу, как часть текущего рендера.
	*/
	void ShaderProgram::use() const
	{
		glUseProgram(_program);
	}

	/**
	* Возврашает строку, содержащую текст ошибки или nullopt.
	* @return текст ошибки или nullopt, если ошибки не было.
	*/
	optional<string> ShaderProgram::getError() const
	{
		assert(_program);

		GLint status = 0;
		glGetProgramiv(_program, GL_LINK_STATUS, &status);

		if (!status) {
			glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &status);
			string error(status, '\0');
			glGetProgramInfoLog(_program, status, nullptr, &error[0]);
			return error;
		}

		return nullopt;
	}

	/**
	* Возвращает индекс шейдерного аттрибута с именем name.
	* @param name имя шейдерного аттрибута.
	* @return индекс шейдерного аттрибута.
	*/
	int ShaderProgram::attributeLocation(const string_view &name) const
	{
		assert(_program);
		return glGetAttribLocation(_program, name.data());
	}

	/**
	* Возвращает индекс uniform-переменной с именем name.
	* @param name имя uniform-переменной.
	* @return индекс.
	*/
	int ShaderProgram::uniformLocation(const string_view &name) const
	{
		assert(_program);
		return glGetUniformLocation(_program, name.data());
	}

	/**
	* Методы устанавливают значение uniform-переменной для текущей шейдерной программы.
	* @param loc индекс переменной.
	* @param v значение переменной.
	*/
	void ShaderProgram::uniform(int loc, int v) const
	{
		assert(_program);
		glUniform1i(loc, v);
	}

	void ShaderProgram::uniform(int loc, float v) const
	{
		assert(_program);
		glUniform1f(loc, v);
	}

	void ShaderProgram::uniform(int loc, const vec2 &v) const
	{
		assert(_program);
		glUniform2fv(loc, 1, value_ptr(v));
	}

	void ShaderProgram::uniform(int loc, const ivec2 &v) const
	{
		assert(_program);
		glUniform2iv(loc, 1, value_ptr(v));
	}
	void ShaderProgram::uniform(int loc, const vec3 &v) const
	{
		assert(_program);
		glUniform3fv(loc, 1, value_ptr(v));
	}

	void ShaderProgram::uniform(int loc, const ivec3 &v) const
	{
		assert(_program);
		glUniform3iv(loc, 1, value_ptr(v));
	}

	void ShaderProgram::uniform(int loc, const vec4 &v) const
	{
		assert(_program);
		glUniform4fv(loc, 1, value_ptr(v));
	}

	void ShaderProgram::uniform(int loc, const ivec4 &v) const
	{
		assert(_program);
		glUniform4iv(loc, 1, value_ptr(v));
	}

	/**
	* Методы устанавливают значение uniform-переменной для текущей шейдерной программы.
	* @param name имя переменной.
	* @param v значение переменной.
	*/
	void ShaderProgram::uniform(const string_view &name, int v) const
	{
		uniform(uniformLocation(name), v);
	}

	void ShaderProgram::uniform(const string_view &name, float v) const
	{
		uniform(uniformLocation(name), v);
	}

	void ShaderProgram::uniform(const string_view &name, const vec2 &v) const
	{
		uniform(uniformLocation(name), v);
	}

	void ShaderProgram::uniform(const string_view &name, const ivec2 &v) const
	{
		uniform(uniformLocation(name), v);
	}

	void ShaderProgram::uniform(const string_view &name, const vec3 &v) const
	{
		uniform(uniformLocation(name), v);
	}

	void ShaderProgram::uniform(const string_view &name, const ivec3 &v) const
	{
		uniform(uniformLocation(name), v);
	}

	void ShaderProgram::uniform(const string_view &name, const vec4 &v) const
	{
		uniform(uniformLocation(name), v);
	}

	void ShaderProgram::uniform(const string_view &name, const ivec4 &v) const
	{
		uniform(uniformLocation(name), v);
	}

	/**
	* Методы устанавливают значение uniform-матрицы для текущей шейдерной программы.
	* @param name имя матрицы.
	* @param v матрица.
	*/
	void ShaderProgram::uniform(const string_view &name, const mat3 &v) const
	{
		int loc = uniformLocation(name);
		glUniformMatrix3fv(loc, 1, GL_FALSE, value_ptr(v));
	}

	void ShaderProgram::uniform(const string_view &name, const mat4 &v) const
	{
		int loc = uniformLocation(name);
		glUniformMatrix4fv(loc, 1, GL_FALSE, value_ptr(v));
	}
}

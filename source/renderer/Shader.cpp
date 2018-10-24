#include <fstream>
#include <stdexcept>
#include <cassert>

#include "Shader.h"

namespace pgl
{
	Shader::Shader(ShaderType type, const string_view &path) :
		_type(type),
		_handle(0)
	{
		string source = LoadFromFile(path);
		_path.assign(path.data());
		Compile(source);
	}

	void Shader::Compile(const string_view &source)
	{
		_handle = glCreateShader(_type);

		if (!_handle) {
			throw runtime_error("Shader can't be created.");
		}

		const char *data = source.data();
		glShaderSource(_handle, 1, &data, nullptr);
		glCompileShader(_handle);

		GLint status = 0;
		glGetShaderiv(_handle, GL_COMPILE_STATUS, &status);
		
		if (!status) {
			glGetShaderiv(_handle, GL_INFO_LOG_LENGTH, &status);
			string error(status, '\0');
			glGetShaderInfoLog(_handle, status, nullptr, &error[0]);
			glDeleteShader(_handle);
			_handle = 0;
			throw runtime_error(error);
		}
	}

	string Shader::LoadFromFile(const string_view &path)
	{
		ifstream file(path.data());

		if (!file) {
			throw runtime_error("File can't be opened.");
		}

		auto buf = file.rdbuf();
		auto size = buf->pubseekoff(0, file.end);
		buf->pubseekoff(0, file.beg);
		string source((unsigned int)size, '\0');
		buf->sgetn(&source[0], size);

		return source;
	}
}
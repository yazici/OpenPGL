#include <stdexcept>
#include <cassert>
#include <fstream>
#include <sstream>

#include <renderer/Shader.h>

namespace pgl
{
	using namespace std;

	Shader::Shader()
		: _shader(0)
	{
	}

	/**
	* Создает и компилирует шейдер.
	* @param type тип шейдера.
	* @param path путь к файлу с исходным кодом.
	*/
	Shader::Shader(ShaderType type, const string_view &path)
		: _type(type), 
		  _path(path),
		  _shader(0)
	{
		string source = loadFromFile(path);
		compile(source);
	}

	Shader::Shader(const Shader &s)
		//: Shader(s._type, s._path)
	{
		_type = s._type;
		_path = s._path;
		_shader = 0;

		// При копировании объекта, созданного при помощи конструктора по умолчанию,
		// будет выброшено исключение "The file can't be opened.", потому что _path.length()
		// равна 0. Для правильного копирования "пустых" объектов необходима конструкция...
		if (_path.length() > 0) {
			compile(_type, _path);
		}
	}

	Shader::Shader(Shader &&s)
		: _path(s._path),
		  _type(s._type)
	{
		_shader = s._shader;
		s._shader = 0;
	}

	/**
	* Удяляет шейдерный объект.
	*/
	Shader::~Shader()
	{
		glDeleteShader(_shader);
	}

	void Shader::compile(ShaderType type, const std::string_view &path)
	{
		if (_shader) {
			throw runtime_error("The shader is already compiled.");
		}

		_type = type;
		_path = path;
		string source = loadFromFile(path);
		compile(source);
	}

	/**
	* Компилирует шейдер с заданным исходным кодом.
	* @param s исходный код шейдера.
	*/
	void Shader::compile(const string_view &s)
	{
		assert(!_shader);
		
		const char *source = s.data();
		_shader = glCreateShader(_type);

		if (!_shader) {
			throw runtime_error("Shader can't be created. OpenGL can't allocate resources.");
		}

		glShaderSource(_shader, 1, &source, nullptr);
		glCompileShader(_shader);
		auto e = getError();

		if (e) {
			stringstream msg;
			msg << "Shader can't be compiled. Log: " << e.value();
			throw runtime_error(msg.str());
		}
	}

	/**
	* Возврашает строку, содержащую текст ошибки или nullopt.
	* @return текст ошибки или nullopt, если ошибки не было.
	*/
	optional<string> Shader::getError() const
	{
		assert(_shader);

		GLint status = 0;
		glGetShaderiv(_shader, GL_COMPILE_STATUS, &status);
		
		if (!status) {
			glGetShaderiv(_shader, GL_INFO_LOG_LENGTH, &status);
			string error(status, '\0');
			glGetShaderInfoLog(_shader, status, nullptr, &error[0]);
			return error;
		}
		
		return nullopt;
	}

	/**
	* Загружает исходный код из файла.
	* @param path путь к файлу с исходным кодом.
	* @return текст, загруженный из файла path.
	*/
	string Shader::loadFromFile(const string_view &path) const
	{
		ifstream file(path.data());

		if (file) {
			auto buf = file.rdbuf();
			stringstream s;
			s << buf;
			return s.str();
		}

		throw invalid_argument("The file can't be opened.");
	}
}

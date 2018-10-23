#ifndef _RENDERER_SHADER_H
#define _RENDERER_SHADER_H

#include <GL/glew.h>
#include <string>
#include <string_view>

using namespace std;

namespace pgl
{
    enum ShaderType : GLenum
    {
        VERTEX   = GL_VERTEX_SHADER,
        FRAGMENT = GL_FRAGMENT_SHADER,
    };

    class Shader
    {
		friend class ShaderProgram;

	public:

		/**
		* Создает шейдер с типом type и исходным кодом из файла path.
		*
		* @param type тип шейдера.
		* @param path путь к файлу с исходным кодом.
		*/
		Shader(ShaderType type, const string_view &path);

	private:

		/**
		* Компилирует шейдер с заданным исходным кодом.
		* @param source исходный код шейдера.
		*/
		void Compile(const string_view &source);

		/**
		* Загружает исходный код из файла.
		* @param path путь к файлу с исходным кодом.
		*/	 
		string LoadFromFile(const string_view &path);

	private:

		string _path;
		ShaderType _type;
		GLuint _handle;
    };
}

#endif //!_RENDERER_SHADER_H

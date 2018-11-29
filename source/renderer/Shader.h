#ifndef _RENDERER_SHADER_H
#define _RENDERER_SHADER_H

#include <optional>
#include <string>
#include <string_view>

#include <GL/glew.h>

namespace pgl
{
    enum ShaderType : GLuint
    {
        VERTEX   = GL_VERTEX_SHADER,
        FRAGMENT = GL_FRAGMENT_SHADER,
        GEOMETRY = GL_GEOMETRY_SHADER,
    };

    class Shader
    {
		friend class ShaderProgram;
    
    public:
    
		Shader();
		Shader(const Shader &s);
		Shader(Shader &&s);

        /**
        * Создает и компилирует шейдер.
        * @param type тип шейдера.
		* @param path путь к файлу с исходным кодом.
        */
        Shader(ShaderType type, const std::string_view &path);

		/**
		* Удяляет шейдерный объект.
		*/
        ~Shader();

		/**
		* Компилирует шейдер.
		* @param type тип шейдера.
		* @param path файл с исходным кодом.
		*/
		void compile(ShaderType type, const std::string_view &path);

    private:

        /**
		* Компилирует шейдер с заданным исходным кодом.
		* @param s исходный код шейдера.
		*/
        void compile(const std::string_view &s);

        /**
        * Возврашает строку, содержащую текст ошибки или nullopt.
        * @return текст ошибки или nullopt, если ошибки не было.
        */
        std::optional<std::string> getError() const;

        /**
		* Загружает исходный код из файла.
		* @param path путь к файлу с исходным кодом.
        * @return текст, загруженный из файла path.
		*/
        std::string loadFromFile(const std::string_view &path) const;

    private:

        std::string _path;
        ShaderType _type;
        GLuint _shader;
    };
}

#endif //!_RENDERER_SHADER_H

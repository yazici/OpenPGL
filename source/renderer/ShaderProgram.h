#ifndef _RENDERER_SHADERPROGRAM_H
#define _RENDERER_SHADERPROGRAM_H

#include <string>
#include <optional>
#include <string_view>
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "renderer/Shader.h"

namespace pgl
{
	class ShaderProgram
	{
	public:

		/**
		* Создает шейдерную программу.
		* @param vert путь к файлу с вершинным шейдером.
		* @param frag путь к файлу с фрагментным шейдером.
		*/
		ShaderProgram(const std::string_view &vert, const std::string_view &frag);

		/**
		* Очищает выделенные ресурсы.
		*/
		~ShaderProgram();

		/**
		* Устанавливает шейдерную программу, как часть текущего рендера.
		*/
		void use() const;

		/**
		* Возвращает индекс шейдерного аттрибута с именем name.
		* @param name имя шейдерного аттрибута.
		* @return индекс шейдерного аттрибута.
		*/
		int attributeLocation(const std::string_view &name) const;

		/**
		* Возвращает индекс uniform-переменной с именем name.
		* @param name имя uniform-переменной.
		* @return индекс.
		*/
		int uniformLocation(const std::string_view &name) const;

		/**
		* Методы устанавливают значение uniform-переменной для текущей шейдерной программы.
		* @param loc индекс переменной.
		* @param v значение переменной.
		*/
		void uniform(int loc, int   v) const;
		void uniform(int loc, float v) const;
		void uniform(int loc, const glm::vec2  &v) const;
		void uniform(int loc, const glm::ivec2 &v) const;
		void uniform(int loc, const glm::vec3  &v) const;
		void uniform(int loc, const glm::ivec3 &v) const;
		void uniform(int loc, const glm::vec4  &v) const;
		void uniform(int loc, const glm::ivec4 &v) const;

		/**
		* Методы устанавливают значение uniform-переменной для текущей шейдерной программы.
		* @param name имя переменной.
		* @param v значение переменной.
		*/
		void uniform(const std::string_view &name, int   v) const;
		void uniform(const std::string_view &name, float v) const;
		void uniform(const std::string_view &name, const glm::vec2  &v) const;
		void uniform(const std::string_view &name, const glm::ivec2 &v) const;
		void uniform(const std::string_view &name, const glm::vec3  &v) const;
		void uniform(const std::string_view &name, const glm::ivec3 &v) const;
		void uniform(const std::string_view &name, const glm::vec4  &v) const;
		void uniform(const std::string_view &name, const glm::ivec4 &v) const;

		/**
		* Методы устанавливают значение uniform-матрицы для текущей шейдерной программы.
		* @param name имя матрицы.
		* @param v матрица.
		*/
		void uniform(const std::string_view &name, const glm::mat3 &v) const;
		void uniform(const std::string_view &name, const glm::mat4 &v) const;

	private:

		ShaderProgram(const ShaderProgram &s) = delete;

		/**
		* Возврашает строку, содержащую текст ошибки или nullopt.
		* @return текст ошибки или nullopt, если ошибки не было.
		*/
		std::optional<std::string> getError() const;

	private:
		Shader _vertex;
		Shader _fragment;
		Shader _geometry;
		GLuint _program;
	};
}

#endif // !_RENDERER_SHADERPROGRAM_H

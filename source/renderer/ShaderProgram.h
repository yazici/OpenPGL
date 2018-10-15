#ifndef _RENDERER_SHADERPROGRAM_H
#define _RENDERER_SHADERPROGRAM_H

#include <GL/glew.h>
#include <string>

#include "Shader.h"

using namespace std;

namespace pgl
{
	class ShaderProgram
	{
	public:
		
		ShaderProgram(const string_view &vert, const string_view &frag);

		void use() const noexcept;

	private:
		Shader _vertex;
		Shader _fragment;
		GLuint _handle;
	};
}

#endif // !_RENDERER_SHADERPROGRAM_H

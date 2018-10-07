#ifndef _RENDERER_TEXTURE_H
#define _RENDERER_TEXTURE_H

#include <GL/glew.h>
#include <vector>

namespace pgl
{
	class Texture
	{
	public:
		Texture();

		Texture(const std::vector<GLubyte>& data, int w, int h);

		Texture(const GLubyte* data, int w, int h);

		~Texture();

		void Create(const std::vector<GLubyte>& data, int w, int h);

		void Create(const GLubyte* data, int w, int h);

		void Bind(GLint slot = 0) const noexcept;

		void Unbind() const noexcept;

		GLint Width() const noexcept;

		GLint Height() const noexcept;

	private:
		std::vector<GLubyte> _data;
		GLuint _tex;
		GLint _w;
		GLint _h;
	};
}


#endif // !_RENDERER_TEXTURE_H

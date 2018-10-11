#include <stdexcept>

#include "Texture.h"

namespace pgl
{
	Texture::Texture() : 
		_w(0), 
		_h(0), 
		_tex(0)
	{

	}

	Texture::Texture(const std::vector<GLubyte>& data, int w, int h) :
		Texture()
	{
		create(data, w, h);
	}

	Texture::Texture(const GLubyte* data, int w, int h) :
		Texture()
	{
		create(data, w, h);
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &_tex);
	}

	void Texture::create(const std::vector<GLubyte> &data, int w, int h)
	{
		if (data.size() != w * h) {
			throw std::runtime_error("The Size of the data must be equal w * h.");
		}

		create(data.data(), w, h);
	}

	void Texture::create(const GLubyte *data, int w, int h)
	{
		if (_tex) {
			throw std::runtime_error("The texture object has been created and cannot be created again.");
		} else if (nullptr == data) {
			throw std::invalid_argument("You passed in a null pointer. The 'data' argument can't be a null pointer.");
		} else if (0 >= w) {
			throw std::invalid_argument("The argument w must be greater than 0.");
		} else if (0 >= h) {
			throw std::invalid_argument("The argument h must be greater than 0.");
		}

		_h = h;
		_w = w;
		_data.assign(data, data + (w * h * 4));

		glGenTextures(1, &_tex);
		glBindTexture(GL_TEXTURE_2D, _tex);
		glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, w, h);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, w, h, GL_RGBA, GL_UNSIGNED_BYTE, _data.data());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	GLint Texture::width() const noexcept
	{
		return _w;
	}

	GLint Texture::height() const noexcept
	{
		return _h;
	}

	void Texture::bind(GLint slot) const noexcept
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, _tex);
	}

	void Texture::unbind() const noexcept
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

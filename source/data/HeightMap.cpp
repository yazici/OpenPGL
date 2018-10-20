#include "HeightMap.h"

namespace pgl
{
	HeightMap::HeightMap(int w, int h, const uint8_t * data) :
		_map(w, h, Texture::BLACK_WHITE, GL_UNSIGNED_BYTE, data);
	{
	}

	HeightMap::HeightMap(const HeightMap & hm) :
		_map(hm._map)
	{
	}

	int HeightMap::width() const noexcept
	{
		return _width;
	}

	int HeightMap::height() const noexcept
	{
		return _height;
	}

	const Texture & HeightMap::texture() const
	{
		return _map;
	}
}

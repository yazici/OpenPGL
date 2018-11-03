//
//  HeightMap.cpp
//
//  Created by Максим Денисенко on 22.10.2018.
//  Copyright © 2018 PCG. All rights reserved.
//

#include <cassert>
#include "data/HeightMap.h"

namespace pgl
{
	HeightMap::HeightMap(size_t w, size_t h, const float *data)
	{
		_init(w, h, data);
	}

	HeightMap::HeightMap(const HeightMap &hm)
	{
		_init(hm._width, hm._height, hm._map.data());
	}

	void HeightMap::_init(size_t w, size_t h, const float *data)
	{
		if (0 == w) {
			throw std::invalid_argument("The width of map can't be zero.");
		} else if (0 == h) {
			throw std::invalid_argument("The height of map can't be zero.");
		}

		_width = w;
		_height = h;

		if (data) {
			_map.assign(data, data + w * h);
		} else {
			_map.assign(w * h, 0.0f);
		}
		
		assert(_map.size() == w * h);
	}

	size_t HeightMap::width() const noexcept
	{
		return _width;
	}

	size_t HeightMap::height() const noexcept
	{
		return _height;
	}

	Texture HeightMap::texture() const
	{
		return Texture(_width, _height, Texture::PixelFormat::BLACK_WHITE, &_map[0]);
	}

	Mesh HeightMap::toMesh() const
	{
		Mesh plane = Mesh::createPlane(_width, 8.0f);

		for (int y = 0; y < _height; ++y) {
			for (int x = 0; x < _width; ++x) {
				plane.vertex(y * _width + x).y = _map[y * _width + x];
			}
		}

		return plane;
	}

	float HeightMap::depth(size_t x, size_t y) const noexcept
	{
		return _map[y * _width + x];
	}

	void HeightMap::depth(size_t x, size_t y, float v) noexcept
	{
		_map[y * _width + x] = v;
	}
}

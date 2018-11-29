//
//  HeightMap.cpp
//
//  Created by Максим Денисенко on 22.10.2018.
//  Copyright © 2018 PCG. All rights reserved.
//

#include <cassert>
#include "data/HeightMap.h"

#include <iostream>

namespace pgl
{
	HeightMap::HeightMap(int w, int h, const float *data)
	{
		_init(w, h, data);
	}

	HeightMap::HeightMap(int w, int h, const float **data)
	{
		if (0 == w) {
			throw std::invalid_argument("The width of map can't be zero.");
		} else if (0 == h) {
			throw std::invalid_argument("The height of map can't be zero.");
		}

		_width = w;
		_height = h;

		if (data) {
			_map.resize(w * h);

			for (int y = 0; y < h; ++y) {
				for (int x = 0; x < w; ++x) {
					_map[y * w + x] = data[y][x];
				}
			}
		} else {
			_map.assign(w * h, 0.0f);
		}

		assert(_map.size() == w * h);
	}

	HeightMap::HeightMap(const HeightMap &hm)
	{
		_init(hm._width, hm._height, hm._map.data());
	}

	void HeightMap::_init(int w, int h, const float *data)
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

	int HeightMap::width() const noexcept
	{
		return _width;
	}

	int HeightMap::height() const noexcept
	{
		return _height;
	}

	Texture HeightMap::texture() const
	{
        Texture tex(_width, _height, {0.0f, 0.0f, 0.0f, 0.0f});
        
        for (size_t i = 0; i < _width; i++) {
            for (size_t j = 0; j < _height; j++) {
                tex.at(i, j).red(_map[i * _height + j]);
            }
        }
        
		return tex;
	}

	Mesh HeightMap::toMesh(float divSize) const
	{
		Mesh plane = Mesh::createPlane(_width - 1, _height - 1, divSize);

		for (int y = 0; y < _height; ++y) {
			for (int x = 0; x < _width; ++x) {
				plane.vertex(y * _width + x).y = _map[y * _width + x];
			}
		}

		plane.calculateNormal();
		return plane;
	}

	float HeightMap::depth(int x, int y) const noexcept
	{
		return _map[y * _width + x];
	}

	void HeightMap::depth(int x, int y, float v) noexcept
	{
		_map[y * _width + x] = v;
	}
}

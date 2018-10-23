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
	HeightMap::HeightMap(size_t w, size_t h, const uint8_t *data) :
		_width(w),
		_height(h),
        _map(w, h, Texture::BLACK_WHITE, data)
	{
	}

	HeightMap::HeightMap(const HeightMap &hm) :
		_width(hm._width),
		_height(hm._height),
		_map(hm._map)
	{
	}

	size_t HeightMap::width() const noexcept
	{
		return _width;
	}

	size_t HeightMap::height() const noexcept
	{
		return _height;
	}

	const Texture & HeightMap::texture() const
	{
		return _map;
	}
    
    uint8_t HeightMap::depth(size_t x, size_t y) const noexcept
    {
		assert(_map._data);
        return _map._data[x * _map._width + y];
    }
    
    void HeightMap::depth(size_t x, size_t y, uint8_t v) noexcept
    {
		assert(_map._data);
        _map._data[x * _map._width + y] = v;
    }
}

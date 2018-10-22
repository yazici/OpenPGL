//
//  HeightMap.cpp
//  createNoise
//
//  Created by Максим Денисенко on 22.10.2018.
//  Copyright © 2018 PCG. All rights reserved.
//


#include "HeightMap.h"

namespace pgl
{
	HeightMap::HeightMap(int w, int h, const uint8_t * data) :
        _map(w, h, Texture::PixelFormat::BLACK_WHITE, data)
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
    
    uint8_t HeightMap::depth(int x, int y) const noexcept
    {
        return _map._data[x * _map._width + y];
    }
    
    void HeightMap::depth(int x, int y, uint8_t v) noexcept
    {
        _map._data[x * _map._width + y] = v;
    }
}

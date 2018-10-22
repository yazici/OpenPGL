//
//  HeightMap.h
//  createNoise
//
//  Created by Максим Денисенко on 22.10.2018.
//  Copyright © 2018 PCG. All rights reserved.
//

#ifndef _DATA_HEIGHTMAP_H
#define _DATA_HEIGHTMAP_H

#include <string>
#include <cstdint>

#include "Texture.h"

using namespace std;

namespace pgl
{
	class HeightMap
	{
	public:
        
        /**
         * Конструктор.
         *
         * @param w ширина карты
         * @param h высота карты
         * @param data массив данных
         */
		HeightMap(int w, int h, const uint8_t *data = nullptr);

		HeightMap(const HeightMap &hm);

		int width() const noexcept;

		int height() const noexcept;
        
        /**
         * Метод с помощью которой можно узнать высоту точки.
         *
         * @param x координата по оси абсцисс
         * @param y координата по оси ордината
         * @return высота точки на карте по координате (x, y)
         */
		uint8_t depth(int x, int y) const noexcept;
        
        /**
         * Метод с помощью которой можно указать высоту точки.
         *
         * @param x координата по оси абсцисс
         * @param y координата по оси ордината
         * @param v высота точки по координате (x, y)
         */
		void depth(int x, int y, uint8_t v) noexcept;

		const Texture& texture() const;

	private:
		Texture _map;
		int _width;
		int _height;
	};
}

#endif // !_DATA_HEIGHTMAP_H
